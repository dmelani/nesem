#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sbc(cpu *c, addressing_mode am) {
	printf("\tSBC: ");
	uint8_t data = isa_load_read(c, am);
	uint8_t carry = c->p & CPU_FLAG_C;
	uint16_t tmp = c->a - data - (c ? 0 : 1);

	printf("0x%0.2x - 0x%0.2x - 0x%0.1x = ", c->a, data, carry ? 0 : 1);

	cpu_set_n(c, tmp & 0xFF);
	cpu_set_z(c, tmp & 0xFF);

	if (((c->a ^ tmp) & 0x80) && ((c->a ^ data) & 0x80)) {
		c->p |= CPU_FLAG_V;
	} else {
		c->p &= ~CPU_FLAG_V;
	}

	if (tmp < 0x100) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	c->a = tmp & 0xFF;
	printf("0x%0.2x Flags: 0x%0.2x\n",  c->a, c->p);
}

ADD_INSTRUCTION(0xe9, SBC, IMMEDIATE, sbc);
ADD_INSTRUCTION(0xe5, SBC, ZERO_PAGE, sbc);
ADD_INSTRUCTION(0xf5, SBC, INDEXED_ZERO_PAGE_X, sbc);
ADD_INSTRUCTION(0xed, SBC, ABSOLUTE, sbc);
ADD_INSTRUCTION(0xfd, SBC, INDEXED_ABSOLUTE_X, sbc);
ADD_INSTRUCTION(0xf9, SBC, INDEXED_ZERO_PAGE_Y, sbc);
ADD_INSTRUCTION(0xe1, SBC, INDEXED_INDIRECT, sbc);
ADD_INSTRUCTION(0xf1, SBC, INDIRECT_INDEXED, sbc);

