#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
lda(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	printf("\tLDA ");

	if (am == ABSOLUTE) {
		uint16_t addr = data | (cpu_advance(c) << 8);
		printf("(0x%0.4x)", addr);
		data = cpu_read(c, addr);
	} else if (am == ZERO_PAGE) {
		printf("(0x%0.2x)", data);
		data = cpu_read(c, data);
	} else if (am == INDEXED_ABSOLUTE_X) {
		uint8_t high = cpu_advance(c); //data | (cpu_advance(c) << 8);
		uint16_t addr = (data | (high << 8)) + c->x;
		if (addr >> 8 != high) {
			printf("+");
			cpu_read(c, (high << 8) | (addr & 0xFF));
		}
		printf("(0x%0.4x)", addr);
		data = cpu_read(c, addr);
	}

	c->a = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf(": 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa5, LDA, ZERO_PAGE, lda);
ADD_INSTRUCTION(0xa9, LDA, IMMEDIATE, lda);
ADD_INSTRUCTION(0xad, LDA, ABSOLUTE, lda);
ADD_INSTRUCTION(0xbd, LDA, INDEXED_ABSOLUTE_X, lda);
