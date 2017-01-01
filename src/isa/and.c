#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
and(cpu *c, addressing_mode am) {
	uint8_t data = isa_load_read(c, am);
	uint8_t prev = c->a;

	c->a &= data;

	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	printf("\tAND: 0x%0.2x & 0x%0.2x = 0x%0.2x Flags: 0x%0.2x\n", prev, data, c->a, c->p);
}

ADD_INSTRUCTION(0x29, AND, IMMEDIATE, and);
ADD_INSTRUCTION(0x25, AND, ZERO_PAGE, and);
ADD_INSTRUCTION(0x35, AND, INDEXED_ZERO_PAGE_X, and);
ADD_INSTRUCTION(0x2d, AND, ABSOLUTE, and);
ADD_INSTRUCTION(0x3d, AND, INDEXED_ABSOLUTE_X, and);
ADD_INSTRUCTION(0x39, AND, INDEXED_ABSOLUTE_Y, and);
ADD_INSTRUCTION(0x21, AND, INDEXED_INDIRECT, and);
ADD_INSTRUCTION(0x31, AND, INDIRECT_INDEXED, and);
