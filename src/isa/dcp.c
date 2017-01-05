#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
dcp(cpu *c, addressing_mode am) {
	printf("\tDCP: ");
	uint16_t addr = isa_load_read_write_addr(c, am);
	uint8_t data = cpu_read(c, addr);

	printf("(0x%0.4x) 0x%0.2x ", addr, data);
	cpu_write(c, addr, data--);

	uint8_t res = c->a - data;
	if (c->a < data) {
		c->p &= ~CPU_FLAG_C;
	} else {
		c->p |= CPU_FLAG_C;
	}

	cpu_set_z(c, res);
	cpu_set_n(c, res);

	printf("to 0x%0.2x and cmp with 0x%0.2x Flags: 0x%0.2x\n", data, c->a, c->p);
	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0xc3, DCP, INDEXED_INDIRECT, dcp);
ADD_INSTRUCTION(0xc7, DCP, ZERO_PAGE, dcp);
ADD_INSTRUCTION(0xcf, DCP, ABSOLUTE, dcp);
ADD_INSTRUCTION(0xd3, DCP, INDIRECT_INDEXED, dcp);
ADD_INSTRUCTION(0xd7, DCP, INDEXED_ZERO_PAGE_X, dcp);
ADD_INSTRUCTION(0xdb, DCP, INDEXED_ABSOLUTE_Y, dcp);
ADD_INSTRUCTION(0xdf, DCP, INDEXED_ABSOLUTE_X, dcp);

