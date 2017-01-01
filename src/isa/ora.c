#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
ora(cpu *c, addressing_mode am) {
	uint8_t data = isa_load_read(c, am);
	uint8_t prev = c->a;

	c->a |= data;

	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	printf("\tORA: 0x%0.2x | 0x%0.2x = 0x%0.2x Flags: 0x%0.2x\n", prev, data, c->a, c->p);
}

ADD_INSTRUCTION(0x09, ORA, IMMEDIATE, ora);
ADD_INSTRUCTION(0x05, ORA, ZERO_PAGE, ora);
ADD_INSTRUCTION(0x15, ORA, INDEXED_ZERO_PAGE_X, ora);
ADD_INSTRUCTION(0x0d, ORA, ABSOLUTE, ora);
ADD_INSTRUCTION(0x1d, ORA, INDEXED_ABSOLUTE_X, ora);
ADD_INSTRUCTION(0x19, ORA, INDEXED_ABSOLUTE_Y, ora);
ADD_INSTRUCTION(0x01, ORA, INDEXED_INDIRECT, ora);
ADD_INSTRUCTION(0x11, ORA, INDIRECT_INDEXED, ora);
