#include "Logging.h"

#include <stdarg.h>
#include <stdio.h>

static int logging_enabled = 0;

void logging_set_enabled(int enabled) {
    logging_enabled = enabled != 0;
}

void log_debug(const char *format, ...) {
    va_list args;

    if (!logging_enabled) {
        return;
    }

    printf("[debug] ");
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    putchar('\n');
}
