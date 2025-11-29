#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdarg.h>

#include <stdbool.h>
#ifndef DEBUG_MODE
#define DEBUG_MODE false
#else
#undef DEBUG_MODE
#define DEBUG_MODE true
#endif // DEBUG_MODE

#define WRITE_ENVVAR 1
#define KEEP_ENVVAR  0

#define MAX_PATH_SIZE 4096

void debug_log(const char *format, ...);

#endif // GLOBAL_H
