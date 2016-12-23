#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "util.h"

#define NES_RAM_SIZE 2048

cpu *
cpu_create() {
	cpu *c = xmalloc(sizeof(*c));	
	c->ram  = xmalloc(NES_RAM_SIZE);

	cpu_reset(c);

	return c;
}

void
cpu_destroy(cpu *c) {
	free(c->ram);
	free(c);
}

void
cpu_reset(cpu *c) {
	char *ram = c->ram;

	memset(c->ram, 0, NES_RAM_SIZE);
	memset(c, 0, sizeof(*c));

	c->ram = ram;
}
