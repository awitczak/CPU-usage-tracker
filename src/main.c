#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// custom includes
#include "fileread.h"
#include "analyzer.h"
#include "logger.h"
#include "queue.h"
#include "mpsc_queue.h"

#define NUM_THREADS 4

/* Time provided in milliseconds for each thread to operate */
#define WATCHDOG_TIMEOUT 2000
#define READER_T 500
#define ANALYZER_T 500
#define PRINTER_T 500
#define LOGGER_T 50

typedef struct {
    pthread_t reader_id;
    pthread_t analyzer_id;
    pthread_t printer_id;
    pthread_t logger_id;

    /* logger queue */
    mpsc_queue_t *logging_queue;

} watchdog_data;

/* mutexes used for the thread responses */
pthread_mutex_t reader_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t analyzer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t printer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t logger_mutex = PTHREAD_MUTEX_INITIALIZER;

/* flags for each thread */
bool reader_is_running = false;
bool analyzer_is_running = false;
bool printer_is_running = false;
bool logger_is_running = false;
bool watchdog_is_running = false;

bool reader_responded = false;
bool analyzer_responded = false;
bool printer_responded = false;
bool logger_responded = false;

CPU_data CPU, CPU_prev;

/* function declarations */
void *reader(void *arg);
void *analyzer(void *arg);
void *printer(void *arg);
void *logger(void *arg);
void *watchdog(void *arg);
bool watchdog_check(pthread_mutex_t *mutex, bool *thread_responded, watchdog_data *wd);
void wait_ms(unsigned int ms);

void *reader(void *arg) {
    reader_is_running = true;

    // queue_t *queue = (queue_t *) arg;
    mpsc_queue_t *logging_queue = (mpsc_queue_t *) arg;

    log_thread_info(logging_queue, "Reader started");

    while (reader_is_running ) {
        wait_ms(READER_T);

        /* signal the watchdog */
        pthread_mutex_lock(&reader_mutex);
        reader_responded = true;
        pthread_mutex_unlock(&reader_mutex);

        // char **data = get_data("/proc/stat");

        // printf("reader-> %s\n", data[0]);
        // free(data);

        log_msg(logging_queue, "Reader ping");
    }

    printf("Reader thread completed.\n");
    return NULL;
}

void *analyzer(void *arg) {
    analyzer_is_running = true;
 
    // queue_t *queue = (queue_t *) arg;
    mpsc_queue_t *logging_queue = (mpsc_queue_t *) arg;

    log_thread_info(logging_queue, "Analyzer started");

    while (analyzer_is_running) {
        wait_ms(ANALYZER_T);

        /* signal the watchdog */
        pthread_mutex_lock(&analyzer_mutex);
        analyzer_responded = true;
        pthread_mutex_unlock(&analyzer_mutex);

        log_msg(logging_queue, "Analyzer ping");
    }

    printf("Analyzer thread completed.\n");
    return NULL;
}

void *printer(void *arg) {
    printer_is_running = true;
 
    mpsc_queue_t *logging_queue = (mpsc_queue_t *) arg;

    log_thread_info(logging_queue, "Printer started");

    while (printer_is_running) {
        wait_ms(PRINTER_T);

        /* signal the watchdog */
        pthread_mutex_lock(&printer_mutex);
        printer_responded = true;
        pthread_mutex_unlock(&printer_mutex);

        log_msg(logging_queue, "Printer ping");
    }

    printf("Printer thread completed.\n");
    return NULL;
}

void *logger(void *arg) {
    logger_is_running = true;

    mpsc_queue_t *logging_queue = (mpsc_queue_t *) arg;

    log_thread_info(logging_queue, "Logger started");

    while (logger_is_running) {
        wait_ms(LOGGER_T);

        /* signal the watchdog */
        pthread_mutex_lock(&logger_mutex);
        logger_responded = true;
        pthread_mutex_unlock(&logger_mutex);

        log_to_file(logging_queue, "../test_log.log");
    }

    printf("Logger thread completed.\n");
    return NULL;
}

void *watchdog(void *arg) {
    watchdog_is_running = true;

    watchdog_data *wd = (watchdog_data *) arg;

    log_thread_info(wd->logging_queue, "Watchdog started");

    while (watchdog_is_running) {

        wait_ms(WATCHDOG_TIMEOUT);

        if (!watchdog_check(&reader_mutex, &reader_responded, wd)) {
            log_error(wd->logging_queue, "Reader stopped responding");
        }
        if (!watchdog_check(&analyzer_mutex, &analyzer_responded, wd)) {
            log_error(wd->logging_queue, "Analyzer stopped responding");
        }
        if (!watchdog_check(&printer_mutex, &printer_responded, wd)) {
            log_error(wd->logging_queue, "Printer stopped responding");
        }
        if (!watchdog_check(&logger_mutex, &logger_responded, wd)) {
            log_error(wd->logging_queue, "Logger stopped responding");
        }
    }

    printf("Watchdog thread completed.\n");
    return NULL;
}

bool watchdog_check(pthread_mutex_t *mutex, bool *thread_responded, watchdog_data *wd) {
    pthread_mutex_lock(mutex);

    if (*thread_responded) {
        *thread_responded = false;
        
        pthread_mutex_unlock(mutex);
        return true;
    }
    else {
        log_msg(wd->logging_queue, "Watchdog triggered, canceling threads");
        pthread_cancel(wd->reader_id);
        pthread_cancel(wd->analyzer_id);
        pthread_cancel(wd->printer_id);
        pthread_cancel(wd->logger_id);

        if (mpsc_queue_destroy(wd->logging_queue)) {
            log_msg(wd->logging_queue, "Logging queue destroyed");
        }
        else {
            log_error(wd->logging_queue, "Failed to destroy the logging queue");
        }

        log_msg(wd->logging_queue, "Threads cancelled successfully");

        pthread_mutex_unlock(mutex);

        return false;
    }
}

void wait_ms(unsigned int ms) {
    struct timespec ts;
    ts.tv_sec = ms/1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;

    nanosleep(&ts, NULL);
}

int main(int argc, char *argv[]) {

    /* Initialize the queue */
    queue_t queue;
    queue_init(&queue);

    /* Initialize the MPSC queue for logging */
    mpsc_queue_t mpsc_queue;
    mpsc_queue_init(&mpsc_queue);

    /* Thread creation */
    watchdog_data wd;
    pthread_t reader_id, analyzer_id, printer_id, logger_id, watchdog_id;

    if (pthread_create(&reader_id, NULL, reader, (void *) &mpsc_queue) != 0) {
        fprintf(stderr, "Unable to create reader thread\n");
        exit(1);
    }

    if (pthread_create(&analyzer_id, NULL, analyzer, (void *) &mpsc_queue) != 0) {
        fprintf(stderr, "Unable to create analyzer thread\n");
        exit(1);
    }

    if (pthread_create(&printer_id, NULL, printer, (void *) &mpsc_queue) != 0) {
        fprintf(stderr, "Unable to create printer thread\n");
        exit(1);
    }

    if (pthread_create(&logger_id, NULL, logger, (void *) &mpsc_queue) != 0) {
        fprintf(stderr, "Unable to create logger thread\n");
        exit(1);
    }

    /* Store the wd of the created threads, and the logger_queue in the watchdog structure*/
    wd.reader_id = reader_id;
    wd.analyzer_id = analyzer_id;
    wd.printer_id = printer_id;
    wd.logger_id = logger_id;
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

    watchdog_is_running = false;
    pthread_cancel(watchdog_id);
    pthread_join(watchdog_id, NULL);
    
    // log_msg(&mpsc_queue, "Program finished\n");

    return 0;
}