#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
slo(cpu *c, addressing_mode am) {
	uint16_t addr = isa_load_read_write_addr(c, am);
	uint8_t data = cpu_read(c, addr);
	uint8_t prev = data;
	uint8_t aprev = c->a;
	cpu_write(c, addr, data);

	data <<= 1;
	c->a |= data;

	if (c->a & (0x01 << 7)) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}
	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	cpu_write(c, addr, data);

	printf("\tSLO: 0x%0.2x => 0x%0.2x | 0x%0.2x = 0x%0.2x Flags: 0x%0.2x\n", aprev, prev, data, c->a, c->p);
}

ADD_INSTRUCTION(0x03, SLO, INDEXED_INDIRECT, slo);
ADD_INSTRUCTION(0x07, SLO, ZERO_PAGE, slo);
ADD_INSTRUCTION(0x0f, SLO, ABSOLUTE, slo);
ADD_INSTRUCTION(0x13, SLO, INDIRECT_INDEXED, slo);
ADD_INSTRUCTION(0x17, SLO, INDEXED_ZERO_PAGE_X, slo);
ADD_INSTRUCTION(0x1b, SLO, INDEXED_ABSOLUTE_Y, slo);
ADD_INSTRUCTION(0x1f, SLO, INDEXED_ABSOLUTE_X, slo);

