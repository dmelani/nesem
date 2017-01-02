#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
ldy(cpu *c, addressing_mode am) {
	printf("\tLDY ");
	uint8_t data = isa_load_read(c, am);

	c->y = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf(": 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa0, LDY, IMMEDIATE, ldy);
ADD_INSTRUCTION(0xa4, LDY, ZERO_PAGE, ldy);
ADD_INSTRUCTION(0xb4, LDX, INDEXED_ZERO_PAGE_X, ldy);
ADD_INSTRUCTION(0xac, LDY, ABSOLUTE, ldy);
ADD_INSTRUCTION(0xbc, LDX, INDEXED_ABSOLUTE_X, ldy);

