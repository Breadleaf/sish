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

// used for setenv calls
#define WRITE_ENVVAR 1
#define KEEP_ENVVAR  0

void debug_log(const char *format, ...);

#endif // GLOBAL_H
