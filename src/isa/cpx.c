#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
cpx(cpu *c, addressing_mode am) {
	printf("\tCPX: ");
	uint8_t data = isa_load_read(c, am);
	uint8_t res = c->x - data;

	if (c->a < data) {
		c->p &= ~CPU_FLAG_C;
	} else {
		c->p |= CPU_FLAG_C;
	}

	cpu_set_n(c, res);
	cpu_set_z(c, res);

	printf("X: 0x%0.2x  Data: 0x%0.2x Flags: 0x%0.2x\n",  c->x, data, c->p);
}

ADD_INSTRUCTION(0xe0, CPX, IMMEDIATE, cpx);
ADD_INSTRUCTION(0xe4, CPX, ZERO_PAGE, cpx);
ADD_INSTRUCTION(0xec, CPX, ABSOLUTE, cpx);

