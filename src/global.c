#include <stdarg.h>
#include <stdio.h>

#include "global.h"

#define DEBUG_PADDING 4

void debug_log(const char *format, ...) {
#if defined DEBUG_MODE && DEBUG_MODE == true
	(void)printf("% *s%s", DEBUG_PADDING, "", "[DEBUG]: ");

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
#else
	return;
#endif
}
