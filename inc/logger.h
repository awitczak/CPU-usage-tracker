/** @file logger.h
 * 
 * @brief Queue creation.
 *
 * @par       
 * 
 */ 

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "mpsc_queue.h"

#define LOG_MSG_ENABLE          1
#define LOG_ERR_ENABLE          1
#define LOG_THREAD_INFO_ENABLE  1
#define LOG_PRINT               1

#define LOG_BUFFER_SIZE 50

void log_msg(mpsc_queue_t *queue, const char *msg);
void log_error(mpsc_queue_t *queue, const char *err);
void log_thread_info(mpsc_queue_t *queue, const char *thread_info);
bool log_to_file(mpsc_queue_t *queue, const char *filepath);
void write_to_file(const char *filepath, const char *msg);

#endif /* LOGGER_H */

