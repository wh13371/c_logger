#include <stdio.h>      /* printf()  */
#include <stdlib.h>     /* EXIT_FAILURE */
#include <time.h>       /* time()  */
#include <sys/time.h>   /* gettimeofday(). localtime(), timeval struct  */
#include <unistd.h>     /* sleep(), getpid()  */
#include "logger.h"

static int run() {
    for (;;) {
        LOG_DEBUG("%ld", time(NULL));
    }
}

int main(int argc, char *argv[]) {

    set_log_level(LOG_INFO);
    LOG_INFO("This goes to stdout only!");

    // set/enable log file output
    if (!set_log_filename("app.log")) {
        return EXIT_FAILURE;
    }

    // set log level to DEBUG
    set_log_level(LOG_DEBUG);

    if (argc > 1) {
        run(); // run the continuous loop test
    }
    else {
        LOG_INFO("Application Started");

        struct timeval epoch;
        struct timezone tz;

        LOG_INFO("Hello, World!");

        const int PID = getpid();
        LOG_DEBUG("PID = %d", PID);

        gettimeofday(&epoch, &tz);
        LOG_DEBUG("epoch = %d.%06ld", epoch.tv_sec, epoch.tv_usec);

        LOG_INFO("Application Stopped");

        set_log_level(LOG_INFO);

        LOG_DEBUG("this won't be logged given log_level changed to INFO");

    }

    close_logger();

    return 0;
}
