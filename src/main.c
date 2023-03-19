#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

// custom includes
#include "fileread.h"
#include "analyzer.h"
#include "logger.h"
#include "rb_queue.h"
#include "mpsc_queue.h"

#define NUM_THREADS 4
#define RING_BUFFER_SIZE 128

#define LOG_FILEPATH "../CPU_Usage_Tracker.log"

/* Time provided in milliseconds for each thread to operate */
#define WATCHDOG_T 2000
#define READER_T 1000
#define ANALYZER_T 1000
#define PRINTER_T 1000
#define LOGGER_T 25

typedef struct {
    rb_queue_t *RA_queue;
    rb_queue_t *AP_queue;
    mpsc_queue_t *logging_queue;

} thread_args_t;

typedef struct {
    pthread_t reader_id;
    pthread_t analyzer_id;
    pthread_t printer_id;
    pthread_t logger_id;

    rb_queue_t *RA_queue;
    rb_queue_t *AP_queue;
    mpsc_queue_t *logging_queue;

} watchdog_args_t;

/* mutexes used for the thread responses */
pthread_mutex_t reader_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t analyzer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t printer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t logger_mutex = PTHREAD_MUTEX_INITIALIZER;

/* flags for thread operation */
bool reader_responded = false;
bool analyzer_responded = false;
bool printer_responded = false;
bool logger_responded = false;

bool watchdog_triggered = false;

volatile sig_atomic_t thread_running = true;

/* function declarations */
void *reader(void *arg);
void *analyzer(void *arg);
void *printer(void *arg);
void *logger(void *arg);
void *watchdog(void *arg);
bool watchdog_check(pthread_mutex_t *mutex, bool *thread_responded, watchdog_args_t *wd);
void watchdog_signal(pthread_mutex_t *mutex, bool *responded);
void wait_ms(unsigned int ms);
void signal_handler(int signum);

void *reader(void *arg) {
    thread_args_t *th = (thread_args_t *) arg;

    log_thread_info(th->logging_queue, "Reader started");

    while (thread_running) {
        wait_ms(READER_T);

        /* signal the watchdog */
        watchdog_signal(&reader_mutex, &reader_responded);

        void **data = get_CPU_data(PROC_STAT_PATH);
        rb_queue_push_back(th->RA_queue, data);   
    }

    write_to_file(LOG_FILEPATH, "Reader completed");
    return NULL;
}

void *analyzer(void *arg) {
    thread_args_t *th = (thread_args_t *) arg;

    /* initialize the structures */
    CPU_data_t *CPU_curr = CPU_data_init(NUM_CORES);
    CPU_data_t *CPU_prev = CPU_data_init(NUM_CORES);

    log_thread_info(th->logging_queue, "Analyzer started");

    while (thread_running) {
        wait_ms(ANALYZER_T);

        /* signal the watchdog */
        watchdog_signal(&analyzer_mutex, &analyzer_responded);

        /* get the data from queue */
        char **data = (char **) rb_queue_pop(th->RA_queue);

        /* process the data and calculate % usage of cores */
        process_CPU_data(CPU_curr, data);

        CPU_usage_t *CPU_usage = CPU_usage_init(NUM_CORES);
        calculate_CPU_usage_percentage(CPU_prev, CPU_curr, CPU_usage);

        /* push the results to queue */
        rb_queue_push_back(th->AP_queue, (void **) CPU_usage);

        /* processing done, store the data */
        store_CPU_data(CPU_prev, CPU_curr);

        /* free up the memory allocated in the reader thread */
        if (data != NULL) {
            for (size_t i = 0; i < (size_t) (NUM_CORES + 1); i++) {
                if (data[i] != NULL) {
                    free(data[i]);
                }
                data[i] = NULL;
        }
            free(data);
            data = NULL;
        }
    }

    /* clean-up */
    CPU_data_clear(CPU_curr);
    CPU_data_clear(CPU_prev);

    write_to_file(LOG_FILEPATH, "Analyzer completed");
    return NULL;
}

void *printer(void *arg) {
    thread_args_t *th = (thread_args_t *) arg;

    log_thread_info(th->logging_queue, "Printer started");

    while (thread_running) {
        wait_ms(PRINTER_T);

        /* signal the watchdog */
        watchdog_signal(&printer_mutex, &printer_responded);

        CPU_usage_t *CPU_usage = (CPU_usage_t *) rb_queue_pop(th->AP_queue);
        print_CPU_usage(CPU_usage);

        /* clean-up */
        CPU_usage_clear(CPU_usage);
    }

    write_to_file(LOG_FILEPATH, "Printer completed");
    return NULL;
}

void *logger(void *arg) {
    thread_args_t *th = (thread_args_t *) arg;

    log_thread_info(th->logging_queue, "Logger started");

    while (thread_running) {
        wait_ms(LOGGER_T);

        /* signal the watchdog */
        watchdog_signal(&logger_mutex, &logger_responded);

        log_to_file(th->logging_queue, LOG_FILEPATH);
    }

    write_to_file(LOG_FILEPATH, "Logger completed");
    return NULL;
}

void *watchdog(void *arg) {
    watchdog_args_t *wd = (watchdog_args_t *) arg;

    log_thread_info(wd->logging_queue, "Watchdog started");

    while (thread_running) {

        wait_ms(WATCHDOG_T);

        if (!watchdog_check(&reader_mutex, &reader_responded, wd)) {
            log_error(wd->logging_queue, "Reader stopped responding");
            break;
        }
        if (!watchdog_check(&analyzer_mutex, &analyzer_responded, wd)) {
            log_error(wd->logging_queue, "Analyzer stopped responding");
            break;
        }
        if (!watchdog_check(&printer_mutex, &printer_responded, wd)) {
            log_error(wd->logging_queue, "Printer stopped responding");
            break;
        }
        if (!watchdog_check(&logger_mutex, &logger_responded, wd)) {
            log_error(wd->logging_queue, "Logger stopped responding");
            break;
        }
    }

    write_to_file(LOG_FILEPATH, "Watchdog completed");
    return NULL;
}

bool watchdog_check(pthread_mutex_t *mutex, bool *thread_responded, watchdog_args_t *wd) {
    pthread_mutex_lock(mutex);

    if (*thread_responded) {
        *thread_responded = false;
        
        pthread_mutex_unlock(mutex);
        return true;
    }
    else {
        log_msg(wd->logging_queue, "Watchdog triggered, canceling threads");
        thread_running = false;

        pthread_cancel(wd->reader_id);
        pthread_cancel(wd->analyzer_id);
        pthread_cancel(wd->printer_id);
        pthread_cancel(wd->logger_id);

        rb_queue_destroy(wd->RA_queue, NUM_CORES);
        rb_queue_destroy(wd->AP_queue, NUM_CORES);
        mpsc_queue_destroy(wd->logging_queue);

        log_msg(wd->logging_queue, "Watchdog cleaned up");

        watchdog_triggered = true;

        pthread_mutex_unlock(mutex);

        return false;
    }
}

void watchdog_signal(pthread_mutex_t *mutex, bool *responded) {
    pthread_mutex_lock(mutex);
    *responded = true;
    pthread_mutex_unlock(mutex);
}

void wait_ms(unsigned int ms) {
    struct timespec ts;
    ts.tv_sec = ms/1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;

    nanosleep(&ts, NULL);
}

void signal_handler(int signum) {
    if (signum == SIGINT) {
        write_to_file(LOG_FILEPATH, "Keyboard interrupt detected");
        thread_running = false;
    }
    if (signum == SIGTERM) {
        write_to_file(LOG_FILEPATH, "SIGTERM detected");
        thread_running = false;
    }
}

int main() {
    /* SIGTERM setup */
    struct sigaction action;
    action.sa_handler = signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    /* Initialize the ring-buffer queues */
    rb_queue_t RA_queue;
    rb_queue_init(&RA_queue, RING_BUFFER_SIZE);
    rb_queue_t AP_queue;
    rb_queue_init(&AP_queue, RING_BUFFER_SIZE);

    /* Initialize the MPSC queue for logging */
    mpsc_queue_t mpsc_queue;
    mpsc_queue_init(&mpsc_queue);

    /* Add the queues to thread args */
    thread_args_t th;
    th.RA_queue = &RA_queue;
    th.AP_queue = &AP_queue;
    th.logging_queue = &mpsc_queue;

    /* Thread creation */
    watchdog_args_t wd;
    pthread_t reader_id, analyzer_id, printer_id, logger_id, watchdog_id;

    if (pthread_create(&reader_id, NULL, reader, (void *) &th) != 0) {
        fprintf(stderr, "Unable to create reader thread\n");
        exit(1);
    }

    if (pthread_create(&analyzer_id, NULL, analyzer, (void *) &th) != 0) {
        fprintf(stderr, "Unable to create analyzer thread\n");
        exit(1);
    }

    if (pthread_create(&printer_id, NULL, printer, (void *) &th) != 0) {
        fprintf(stderr, "Unable to create printer thread\n");
        exit(1);
    }

    if (pthread_create(&logger_id, NULL, logger, (void *) &th) != 0) {
        fprintf(stderr, "Unable to create logger thread\n");
        exit(1);
    }

    /* Store the wd of the created threads, and the logger_queue in the watchdog structure*/
    wd.reader_id = reader_id;
    wd.analyzer_id = analyzer_id;
    wd.printer_id = printer_id;
    wd.logger_id = logger_id;

    wd.RA_queue = &RA_queue;
    wd.AP_queue = &AP_queue;
    wd.logging_queue = &mpsc_queue;

    if (pthread_create(&watchdog_id, NULL, watchdog, (void*) &wd) != 0) {
        fprintf(stderr, "Unable to create watchdog thread\n");
        exit(1);
    }

    /* Wait for the threads to exit */
    pthread_join(reader_id, NULL);
    pthread_join(analyzer_id, NULL);
    pthread_join(printer_id, NULL);
    pthread_join(logger_id, NULL);
    pthread_join(watchdog_id, NULL);

    write_to_file(LOG_FILEPATH, "All threads joined");

    /* Destroy the queues */
    if (!watchdog_triggered) {
        rb_queue_destroy(&RA_queue, NUM_CORES);
        rb_queue_destroy(&AP_queue, NUM_CORES);
        mpsc_queue_destroy(&mpsc_queue);

        write_to_file(LOG_FILEPATH, "All queues destroyed");
    }

    write_to_file(LOG_FILEPATH, "Program finished");

    return 0;
}