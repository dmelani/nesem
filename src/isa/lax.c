#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
lax(cpu *c, addressing_mode am) {
	printf("\tLAX ");
	uint8_t data = isa_load_read(c, am);

	c->a = data;
	c->x = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf(": 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

/* Undocumented instructions */
ADD_INSTRUCTION(0xa7, LAX, ZERO_PAGE, lax);
ADD_INSTRUCTION(0xa3, LAX, INDEXED_INDIRECT, lax);
ADD_INSTRUCTION(0xaf, LAX, ABSOLUTE, lax);
ADD_INSTRUCTION(0xb3, LAX, INDIRECT_INDEXED, lax);
ADD_INSTRUCTION(0xb7, LAX, INDEXED_ZERO_PAGE_Y, lax);
ADD_INSTRUCTION(0xbf, LAX, INDEXED_ABSOLUTE_Y, lax);
