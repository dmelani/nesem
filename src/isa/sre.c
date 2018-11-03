#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sre(cpu *c, addressing_mode am) {
	uint16_t addr = 0x00;	
	uint8_t data;
	
	/* Load */
	addr = isa_load_read_write_addr(c, am);
	data = cpu_read(c, addr);
	cpu_write(c, addr, data); // According to http://nesdev.com/6502_cpu.txt

	/* Op */
	printf("\tSRE: 0x%0.2x -> ", data);

	if (data & 0x01) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	data >>= 1;

	printf("0x%0.2x & 0x%0.2x => ", data, c->a);

	c->a ^= data;
	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	printf("0x%0.2x Flags: 0x%0.2x\n", c->a, c->p);

	/* Store */
	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0x43, SRE, INDEXED_INDIRECT, sre);
ADD_INSTRUCTION(0x47, SRE, ZERO_PAGE, sre);
ADD_INSTRUCTION(0x4f, SRE, ABSOLUTE, sre);
ADD_INSTRUCTION(0x53, SRE, INDIRECT_INDEXED, sre);
ADD_INSTRUCTION(0x57, SRE, INDEXED_ZERO_PAGE_X, sre);
ADD_INSTRUCTION(0x5b, SRE, INDEXED_ABSOLUTE_Y, sre);
ADD_INSTRUCTION(0x5f, SRE, INDEXED_ABSOLUTE_X, sre);

