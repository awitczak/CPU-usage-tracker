#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// custom includes
#include "fileread.h"
#include "analyzer.h"
#include "queue.h"

#define NUM_THREADS 4

/* Time provided in milliseconds for each thread to operate */
#define WATCHDOG_TIMEOUT 2000
#define READER_T 1000
#define ANALYZER_T 500
#define PRINTER_T 500
#define LOGGER_T 500

typedef struct {
    pthread_t reader_id;
    pthread_t analyzer_id;
    pthread_t printer_id;
    pthread_t logger_id;
} thread_IDs;

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
queue_t test_queue;

/* function declarations */
void *reader(void *arg);
void *analyzer(void *arg);
void *printer(void *arg);
void *logger(void *arg);
void *watchdog(void *arg);
bool watchdog_check(pthread_mutex_t *mutex, bool *thread_responded, thread_IDs *IDs);
void wait_ms(unsigned int ms);

void *reader(void *arg) {
    reader_is_running = true;
    printf("Reader thread started.\n");
    
    while (reader_is_running ) {
        wait_ms(READER_T);
        // printf("Reader thread still alive.\n");

        /* signal the watchdog */
        pthread_mutex_lock(&reader_mutex);
        reader_responded = true;
        pthread_mutex_unlock(&reader_mutex);

        char **data = get_data("/proc/stat");

        printf("%s\n", data[0]);

        free(data);

        // queue_push(&test_queue, )
    }

    printf("Reader thread completed.\n");
    return NULL;
}

void *analyzer(void *arg) {
    analyzer_is_running = true;
    printf("Analyzer thread started.\n");

    while (analyzer_is_running) {
        wait_ms(ANALYZER_T);
        // printf("Analyzer thread still alive.\n");

        /* signal the watchdog */
        pthread_mutex_lock(&analyzer_mutex);
        analyzer_responded = true;
        pthread_mutex_unlock(&analyzer_mutex);
    }

    printf("Analyzer thread completed.\n");
    return NULL;
}

void *printer(void *arg) {
    printer_is_running = true;
    printf("Printer thread started.\n");

    while (printer_is_running) {
        wait_ms(PRINTER_T);
        // printf("Printer thread still alive.\n");

        /* signal the watchdog */
        pthread_mutex_lock(&printer_mutex);
        printer_responded = true;
        pthread_mutex_unlock(&printer_mutex);
    }

    printf("Printer thread completed.\n");
    return NULL;
}

void *logger(void *arg) {
    logger_is_running = true;
    printf("Logger thread started.\n");

    while (logger_is_running) {
        wait_ms(LOGGER_T);
        // printf("Logger thread still alive.\n");

        /* signal the watchdog */
        pthread_mutex_lock(&logger_mutex);
        logger_responded = true;
        pthread_mutex_unlock(&logger_mutex);
    }

    printf("Logger thread completed.\n");
    return NULL;
}

void *watchdog(void *arg) {
    watchdog_is_running = true;
    printf("Watchdog thread started.\n");

    thread_IDs *IDs = (thread_IDs *) arg;

    printf("%ld %ld %ld %ld\n", IDs->reader_id, IDs->analyzer_id, IDs->printer_id, IDs->logger_id);

    while (watchdog_is_running) {

        wait_ms(WATCHDOG_TIMEOUT);

        if (!watchdog_check(&reader_mutex, &reader_responded, IDs)) {
            printf("Reader thread stopped responding.\n");
        }
        if (!watchdog_check(&analyzer_mutex, &analyzer_responded, IDs)) {
            printf("Analyzer thread stopped responding.\n");
        }
        if (!watchdog_check(&printer_mutex, &printer_responded, IDs)) {
            printf("Printer thread stopped responding.\n");
        }
        if (!watchdog_check(&logger_mutex, &logger_responded, IDs)) {
            printf("Logger thread stopped responding.\n");
        }

        printf("Watchdog watches!\n");
    }

    printf("Watchdog thread completed.\n");
    return NULL;
}

bool watchdog_check(pthread_mutex_t *mutex, bool *thread_responded, thread_IDs *IDs) {
    pthread_mutex_lock(mutex);

    if (*thread_responded) {
        *thread_responded = false;
        
        pthread_mutex_unlock(mutex);
        return true;
    }
    else {
        printf("Watchdog timeout reached. Proceeding to cancel all threads.\n");
        pthread_cancel(IDs->reader_id);
        pthread_cancel(IDs->analyzer_id);
        pthread_cancel(IDs->printer_id);
        pthread_cancel(IDs->logger_id);
        printf("All threads have been canceled.\n");

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
    queue_init(&test_queue, QUEUE_SIZE);
    
    thread_IDs IDs;
    pthread_t reader_id, analyzer_id, printer_id, logger_id, watchdog_id;

    /* Thread creation */
    if (pthread_create(&reader_id, NULL, reader, NULL) != 0) {
        fprintf (stderr, "Unable to create reader thread\n");
        exit(1);
    }

    if (pthread_create(&analyzer_id, NULL, analyzer, NULL) != 0) {
        fprintf (stderr, "Unable to create analyzer thread\n");
        exit(1);
    }

    if (pthread_create(&printer_id, NULL, printer, NULL) != 0) {
        fprintf (stderr, "Unable to create printer thread\n");
        exit(1);
    }

    if (pthread_create(&logger_id, NULL, logger, NULL) != 0) {
        fprintf (stderr, "Unable to create logger thread\n");
        exit(1);
    }

    /* Store the IDs of the created threads in the structure */
    IDs.reader_id = reader_id;
    IDs.analyzer_id = analyzer_id;
    IDs.printer_id = printer_id;
    IDs.logger_id = logger_id;

    // printf("Before watchdog -> %ld %ld %ld %ld\n", data.reader_id, data.analyzer_id, data.printer_id, data.logger_id);

    if (pthread_create(&watchdog_id, NULL, watchdog, (void*) &IDs) != 0) {
        fprintf (stderr, "Unable to create watchdog thread\n");
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
    
    printf("Program completed!\n");

    return 0;
}