#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
lda(cpu *c, addressing_mode am) {
	printf("\tLDA ");
	uint8_t data = isa_load_read(c, am);

	c->a = data;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	printf(": 0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0xa9, LDA, IMMEDIATE, lda);
ADD_INSTRUCTION(0xa5, LDA, ZERO_PAGE, lda);
ADD_INSTRUCTION(0xb5, LDA, INDEXED_ZERO_PAGE_X, lda);
ADD_INSTRUCTION(0xad, LDA, ABSOLUTE, lda);
ADD_INSTRUCTION(0xbd, LDA, INDEXED_ABSOLUTE_X, lda);
ADD_INSTRUCTION(0xb9, LDA, INDEXED_ABSOLUTE_Y, lda);
ADD_INSTRUCTION(0xa1, LDA, INDEXED_INDIRECT, lda);
ADD_INSTRUCTION(0xb1, LDA, INDIRECT_INDEXED, lda);
