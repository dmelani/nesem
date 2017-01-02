#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
cmp(cpu *c, addressing_mode am) {
	printf("\tCMP: ");
	uint8_t data = isa_load_read(c, am);
	uint8_t res = c->a - data;

	if (c->a < data) {
		c->p &= ~CPU_FLAG_C;
	} else {
		c->p |= CPU_FLAG_C;
	}

	cpu_set_n(c, res);
	cpu_set_z(c, res);

	printf("A: 0x%0.2x  Op: 0x%0.2x Flags: 0x%0.2x\n",  c->a, data, c->p);
}

ADD_INSTRUCTION(0xC9, CMP, IMMEDIATE, cmp);
ADD_INSTRUCTION(0xc5, CMP, ZERO_PAGE, cmp);
ADD_INSTRUCTION(0xd5, CMP, INDEXED_ZERO_PAGE_X, cmp);
ADD_INSTRUCTION(0xcd, CMP, ABSOLUTE, cmp);
ADD_INSTRUCTION(0xdd, CMP, INDEXED_ABSOLUTE_X, cmp);
ADD_INSTRUCTION(0xd9, CMP, INDEXED_ABSOLUTE_Y, cmp);
ADD_INSTRUCTION(0xc1, CMP, INDEXED_INDIRECT, cmp);
ADD_INSTRUCTION(0xd1, CMP, INDIRECT_INDEXED, cmp);
