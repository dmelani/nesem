#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
ldy(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	printf("\tLDY ");

	if (am == ABSOLUTE) {
		uint16_t addr = data | (cpu_advance(c) << 8);
		printf("(0x%0.4x)", addr);
		data = cpu_read(c, addr);
	} else if (am == ZERO_PAGE) {
		printf("(0x%0.2x)", data);
		data = cpu_read(c, data);
	}

	c->y = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf(": 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa0, LDY, IMMEDIATE, ldy);
ADD_INSTRUCTION(0xa4, LDY, ZERO_PAGE, ldy);
ADD_INSTRUCTION(0xac, LDY, ABSOLUTE, ldy);

