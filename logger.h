#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>       // printf()
#include <time.h>       // localtime()
#include <stdarg.h>     // va_list - variable args
#include <unistd.h>     // getpid()
#include <sys/time.h>   // gettimeofday()

#define LOG_MAX_LEN    1024

void LOG(const char *fmt, ...);

#endif // LOGGER_H
