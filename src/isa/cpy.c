#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
cpy(cpu *c, addressing_mode am) {
	printf("\tCPY: ");
	uint8_t data = isa_load_read(c, am);
	uint8_t res = c->y - data;

	if (c->a < data) {
		c->p &= ~CPU_FLAG_C;
	} else {
		c->p |= CPU_FLAG_C;
	}

	cpu_set_n(c, res);
	cpu_set_z(c, res);

	printf("\tY: 0x%0.2x  Data: 0x%0.2x Flags: 0x%0.2x\n",  c->y, data, c->p);
}

ADD_INSTRUCTION(0xc0, CPY, IMMEDIATE, cpy);
ADD_INSTRUCTION(0xc4, CPY, ZERO_PAGE, cpy);
ADD_INSTRUCTION(0xcc, CPY, ABSOLUTE, cpy);

