#include <stdio.h>
#include "logger.h"

int main(void) {

    LOG("Application Started");

    struct timeval epoch;
    struct timezone tz;

    LOG("Hello, World!");
    LOG("Hello %s", "World");

    const int PID = getpid();
    LOG("PID = %d", PID);

    gettimeofday(&epoch, &tz);
    LOG("epoch = %d.%06ld", epoch.tv_sec, epoch.tv_usec);

    LOG("Application Stopped");

    return 0;
}
