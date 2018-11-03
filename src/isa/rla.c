#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
rla(cpu *c, addressing_mode am) {
	uint16_t addr = 0x00;	
	uint8_t prev = c->p;
	uint8_t data;
	
	/* Load */
	addr = isa_load_read_write_addr(c, am);
	data = cpu_read(c, addr);
	cpu_write(c, addr, data); // According to http://nesdev.com/6502_cpu.txt

	/* Op */
	printf("\tRLA: 0x%0.2x -> ", data);

	if (data & (0x01 << 7)) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	data <<= 1;
	if (prev & CPU_FLAG_C)
		data |= 0x01;

	printf("0x%0.2x & 0x%0.2x => ", data, c->a);

	c->a &= data;
	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	printf("0x%0.2x Flags: 0x%0.2x\n", c->a, c->p);

	/* Store */
	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0x23, RLA, INDEXED_INDIRECT, rla);
ADD_INSTRUCTION(0x27, RLA, ZERO_PAGE, rla);
ADD_INSTRUCTION(0x2f, RLA, ABSOLUTE, rla);
ADD_INSTRUCTION(0x33, RLA, INDIRECT_INDEXED, rla);
ADD_INSTRUCTION(0x37, RLA, INDEXED_ZERO_PAGE_X, rla);
ADD_INSTRUCTION(0x3b, RLA, INDEXED_ABSOLUTE_Y, rla);
ADD_INSTRUCTION(0x3f, RLA, INDEXED_ABSOLUTE_X, rla);

