#include "logger.h"

static void LOGGER(const char *msg) {
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);
    struct timeval epoch;
    struct timezone tz;

    gettimeofday(&epoch, &tz);
    int PID = getpid();

    printf("{\"timestamp\": \"%04d-%02d-%02d %02d:%02d:%02d.%06ld\", \"epoch\": %ld.%06ld, \"pid\":%d, \"message\": \"%s\"}\n",
            local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
            local_time->tm_hour, local_time->tm_min, local_time->tm_sec, epoch.tv_usec,
            epoch.tv_sec, epoch.tv_usec, PID, msg);
}

void LOG(const char *fmt, ...) {
    va_list va;
    char msg[LOG_MAX_LEN];

    va_start(va, fmt);
    vsnprintf(msg, sizeof(msg), fmt, va); // write formatted data from variable argument list to sized buffer
    va_end(va);

    LOGGER(msg);
}
