#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
eor(cpu *c, addressing_mode am) {
	uint8_t data = isa_load_read(c, am);
	uint8_t prev = c->a;

	c->a ^= data;

	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	printf("\tEOR: 0x%0.2x ^ 0x%0.2x = 0x%0.2x Flags: 0x%0.2x\n", prev, data, c->a, c->p);
}

ADD_INSTRUCTION(0x49, EOR, IMMEDIATE, eor);
ADD_INSTRUCTION(0x45, EOR, ZERO_PAGE, eor);
ADD_INSTRUCTION(0x55, EOR, INDEXED_ZERO_PAGE_X, eor);
ADD_INSTRUCTION(0x4d, EOR, ABSOLUTE, eor);
ADD_INSTRUCTION(0x5d, EOR, INDEXED_ABSOLUTE_X, eor);
ADD_INSTRUCTION(0x59, EOR, INDEXED_ABSOLUTE_Y, eor);
ADD_INSTRUCTION(0x41, EOR, INDEXED_INDIRECT, eor);
ADD_INSTRUCTION(0x51, EOR, INDIRECT_INDEXED, eor);
