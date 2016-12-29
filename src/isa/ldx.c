#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
ldx(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	c->x = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf("\tLDX: 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa2, LDX, IMMEDIATE, ldx);

