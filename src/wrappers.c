/*	SuperDuperSecretProject3
	gaaaah
*/

#include <coreinit/debug.h>
#include <stdarg.h>
#include <stdio.h>

//The emulation core has some rather useful printfs that I'd rather not waste.
void __wrap_printf(const char* fmt, ...) {
	char buf[256];
	va_list arguments;
	va_start(arguments, fmt);
	vsnprintf(buf, 255, fmt, arguments);
	va_end(arguments);
	OSReport(buf);
}
