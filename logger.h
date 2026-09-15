#ifndef LOGGER_H
#define LOGGER_H

#define LOG_MAX_LEN    2048

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

void set_log_level(LogLevel log_level);
int set_log_filename(const char *log_filename);
void _LOG(LogLevel log_level, const char *file, int line, const char *fmt, ...);
void close_logger();

#define LOG_INFO(fmt, ...)  _LOG(LOG_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) _LOG(LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  _LOG(LOG_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) _LOG(LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif // LOGGER_H
