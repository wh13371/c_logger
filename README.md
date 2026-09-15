# a simple C NDJSON Logger (c_logger)

A lightweight, zero-dependency C logging library that outputs structured logs in **NDJSON format**. 

It automatically captures process IDs (PID), high-resolution microsecond timestamps, file names, and line numbers. 

It supports multiple log levels and concurrent logging to both `stdout` and a dedicated log file.

## Features

- **Structured NDJSON Output:**
- **Microsecond Precision:** Uses `gettimeofday` to capture granular execution metrics.
- **Auto-Contextualization:** Macros automatically inject `__FILE__`, `__LINE__`, and the current process ID (`pid`).
- **Flexible Destinations:** Always streams to `stdout`, with an optional secondary stream to a log file.
- **Log Level Severity Filtering:**

## Log Format Example

Every log entry outputs as a single-line JSON payload structured like this:

```json
{"timestamp":"2026-09-15 15:00:00.123456","epoch":1789484400.123456,"pid":12345,"level":"INFO","__file__":"main.c","__line__":27,"message":"Application Started"}
```

## API Reference

### Log Levels
```c
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;
```

### Functions
- `void set_log_level(LogLevel log_level);`  
  Sets the log level severity, lower severity logs will be ignored.
- `int set_log_filename(const char * log_filename);`  
  Enables logging to a log file.
- `void close_logger();`  
  Closes the file stream cleanly and flushes resources.

### Logging Macros
Use these directly in your code, they handle variable argument formatting (like `printf`) automatically:
- `LOG_DEBUG(fmt, ...)`
- `LOG_INFO(fmt, ...)`
- `LOG_WARN(fmt, ...)`
- `LOG_ERROR(fmt, ...)`

## Quick Start Example

Here is a quick look at how to initialize, configure, and use the logger based on `main.c`:

```c
#include "logger.h"
#include <stdlib.h>

int main() {
    // 1. Initialise with a default minimum log level
    set_log_level(LOG_INFO);
    
    // This logs only to stdout
    LOG_INFO("This goes to stdout only!");

    // 2. Optional: Enable file logging
    if (!set_log_filename("app.log")) {
        return EXIT_FAILURE;
    }

    // 3. Adjust log level at runtime if needed
    set_log_level(LOG_DEBUG);

    LOG_INFO("Application Started");
    LOG_DEBUG("PID tracking and microsecond timestamps are active.");
    LOG_WARN("This is a warning log message.");
    
    // 4. Clean up resources before exit
    close_logger();
    return 0;
}
```

## Compilation

Compile the logger components directly alongside your application source files:

```bash
gcc main.c logger.c -o app
```
