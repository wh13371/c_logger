#include "logger.h"
#include <stdio.h>      /* printf()  */
#include <time.h>       /* time()  */
#include <sys/time.h>   /* gettimeofday(). localtime(), timeval struct  */
//#include <string.h>     /* strcpy()  */
#include <unistd.h>     /* sleep(), getpid()  */
//#include <stdbool.h>    /* boolean type */
#include <stdarg.h>     /* va_list */

static FILE *log_file = NULL;
static LogLevel _level = LOG_INFO;

void set_log_level(LogLevel log_level) {
    _level = log_level;
}

int set_log_filename(const char *log_filename) {
    log_file = fopen(log_filename, "w");
    if (log_file == NULL) {
        perror("!!! failed to open log file !!!");
        return false;
    }
    return true;
}

void _LOG(const LogLevel log_level, const char *__file__, const int __line__, const char *fmt, ...) {
    if (log_level < _level) // ignore logs below severity level
        return;

    struct timeval tv; // time in seconds and microseconds
    struct timezone tz; // timezone
    gettimeofday(&tv, NULL);  /* Unix timestamp in seconds & usecs, since 00:00:00 UTC, 1/1/1970 */
    //time_t t = time(NULL); /* Unix timestamp in seconds only since 00:00:00 UTC, 1/1/1970 */
    time_t t = tv.tv_sec;    /* populate time_t with Unix seconds already obtained with gettimeofday() */
    struct tm* local_time = localtime(&t); /* converts a time_t value into a struct tm to allow better timestamp formatting below */

    const char* level_strings[] = { "DEBUG", "INFO", "WARN", "ERROR" };

    va_list va;
    char message[LOG_MAX_LEN];
    va_start(va, fmt);
    vsnprintf(message, sizeof(message), fmt, va); // write formatted data from variable argument list to sized buffer
    va_end(va);

    const int PID = getpid();

    char json_payload[LOG_MAX_LEN * 2];
    snprintf(json_payload, sizeof(json_payload),
            "{\"timestamp\":\"%04d-%02d-%02d %02d:%02d:%02d.%06ld\","
            "\"epoch\":%ld.%06ld,"
            "\"pid\":%d,"
            "\"level\":\"%s\","
            "\"__file__\":\"%s\","
            "\"__line__\":%d,"
            "\"message\":\"%s\"}\n",
            local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
            local_time->tm_hour, local_time->tm_min, local_time->tm_sec, (long)tv.tv_usec,
            (long)tv.tv_sec, (long)tv.tv_usec,
            PID,
            level_strings[log_level],
            __file__,
            __line__,
            message);

    // always to stdout
    fprintf(stdout, "%s", json_payload);
    fflush(stdout);

    // optional to log file
    if (log_file != NULL) {
        fprintf(log_file, "%s", json_payload);
        fflush(log_file);
    }
}

void close_logger() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}
