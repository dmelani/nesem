#include <stdio.h>
#include <stdlib.h>

#include "util.h"

void *
xmalloc(size_t size) {
	void *new_mem = malloc(size);

	if (new_mem == NULL) {
		fprintf(stderr, "fatal: memory exhausted (xmalloc of %ld bytes).\n", size);
		exit(EXIT_FAILURE);
	}

	return new_mem;
}

