#ifndef _UTIL_H
#define _UTIL_H
#include <stdio.h>

#define LOG_TAG(t) static char _log_tag[] = t
#define LOG(...) {printf("%s: ", _log_tag); printf(__VA_ARGS__); printf("\n");}

void *xmalloc(size_t size);

#endif
