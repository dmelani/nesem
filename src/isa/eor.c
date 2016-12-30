#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
eor(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	uint8_t prev = c->a;

	if (am == ABSOLUTE) {
		uint16_t addr = data | (cpu_advance(c) << 8);
		data = cpu_read(c, addr);
	} else if (am == ZERO_PAGE) {
		data = cpu_read(c, data);
	}

	c->a ^= data;

	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	printf("\tEOR: 0x%0.2x | 0x%0.2x = 0x%0.2x Flags: 0x%0.2x\n", prev, data, c->a, c->p);
}

ADD_INSTRUCTION(0x4d, EOR, ABSOLUTE, eor);
ADD_INSTRUCTION(0x49, EOR, IMMEDIATE, eor);
ADD_INSTRUCTION(0x45, EOR, ZERO_PAGE, eor);

