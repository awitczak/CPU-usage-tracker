#include "logger.h"

void log_msg(mpsc_queue_t *queue, const char *msg) {
    if (LOG_MSG_ENABLE) {
        mpsc_queue_push_back(queue, (void *) msg);
    }
    if (LOG_MSG_ENABLE && LOG_PRINT) {
        printf("LOG:MSG>>  %s\n", msg);
    }
}

void log_error(mpsc_queue_t *queue, const char *err) {
    if (LOG_ERR_ENABLE) {
        mpsc_queue_push_back(queue, (void *) err);
    }
    if (LOG_ERR_ENABLE && LOG_PRINT) {
        printf("LOG:ERR>>  %s\n", err);
    }
}

void log_thread_info(mpsc_queue_t *queue, const char *thread_info) {
    if (LOG_THREAD_INFO_ENABLE) {
        mpsc_queue_push_back(queue, (void *) thread_info);
    }
    if (LOG_THREAD_INFO_ENABLE && LOG_PRINT) {
        printf("LOG:THREAD>>  %s\n", thread_info);
    }
}

bool log_to_file(mpsc_queue_t *queue, const char *filepath) {

    /* check if queue is not empty */
    if (get_mpsc_queue_size(queue)) {

        /* create a timestamp for the log */
        time_t now = time(NULL);
        char *timestamp = ctime(&now);
        timestamp[strlen(timestamp)-1] = '\0';

        /* get data from queue */
        char *data = (char *) mpsc_queue_pop(queue);

        /* prepare the logging msg */
        char buffer[LOG_BUFFER_SIZE];
        sprintf(buffer, "[%s] -> %s", timestamp, data);

        /* write to the log file */
        write_to_file(filepath, buffer);
    }

    return true;
}

void write_to_file(const char *filepath, const char *msg) {
    FILE* pFile = fopen(filepath, "a");

    if (pFile == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    fprintf(pFile, "%s\n", msg);
    fclose(pFile);
}
