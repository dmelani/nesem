#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
cpx(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	uint8_t res = c->x - data;

	if (c->a < data) {
		c->p &= ~CPU_FLAG_C;
	} else {
		c->p |= CPU_FLAG_C;
	}

	cpu_set_n(c, res);
	cpu_set_z(c, res);

	printf("\tCPX: X: 0x%0.2x  Op: 0x%0.2x Flags: 0x%0.2x\n",  c->x, data, c->p);
}

ADD_INSTRUCTION(0xe0, CPX, IMMEDIATE, cpx);

