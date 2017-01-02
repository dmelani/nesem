#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
ldx(cpu *c, addressing_mode am) {
	printf("\tLDX ");
	uint8_t data = isa_load_read(c, am);

	c->x = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf(": 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa2, LDX, IMMEDIATE, ldx);
ADD_INSTRUCTION(0xa6, LDX, ZERO_PAGE, ldx);
ADD_INSTRUCTION(0xb6, LDX, INDEXED_ZERO_PAGE_Y, ldx);
ADD_INSTRUCTION(0xae, LDX, ABSOLUTE, ldx);
ADD_INSTRUCTION(0xbe, LDX, INDEXED_ABSOLUTE_Y, ldx);
