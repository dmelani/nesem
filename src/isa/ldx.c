#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
ldx(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	printf("\tLDX ");

	if (am == ABSOLUTE) {
		uint16_t addr = data | (cpu_advance(c) << 8);
		printf("(0x%0.4x)", addr);
		data = cpu_read(c, addr);
	} else if (am == ZERO_PAGE) {
		printf("(0x%0.2x)", data);
		data = cpu_read(c, data);
	}

	c->x = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf(": 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa2, LDX, IMMEDIATE, ldx);
ADD_INSTRUCTION(0xa6, LDA, ZERO_PAGE, ldx);
ADD_INSTRUCTION(0xae, LDA, ABSOLUTE, ldx);
