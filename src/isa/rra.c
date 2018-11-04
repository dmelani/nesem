#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
rra(cpu *c, addressing_mode am) {
	uint16_t addr = 0x00;	
	uint8_t prev = c->p;
	uint8_t data;
	
	/* Load */
	addr = isa_load_read_write_addr(c, am);
	data = cpu_read(c, addr);
	cpu_write(c, addr, data); // According to http://nesdev.com/6502_cpu.txt

	/* Op */
	printf("\tRRA: 0x%0.2x -> ", data);

	if (data & 0x01) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	data >>= 1;
	if (prev & CPU_FLAG_C)
		data |= 1 << 7;


	uint8_t carry = c->p & CPU_FLAG_C;
	uint16_t tmp = c->a + data + (carry ? 1 : 0);

	printf("0x%0.2x + 0x%0.2x + 0x%0.1x = ", c->a, data, carry ? 1 : 0);
	
	if (!((c->a ^ tmp) & 0x80) && ((c->a ^ data) & 0x80)) {
		c->p |= CPU_FLAG_V;
	} else {
		c->p &= ~CPU_FLAG_V;
	}

	if (tmp > 0xFF) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	c->a = tmp & 0xFF;

	cpu_set_n(c, c->a);
	cpu_set_z(c, c->a);

	printf("0x%0.2x Flags: 0x%0.2x\n", c->a, c->p);

	/* Store */
	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0x63, RRA, INDEXED_INDIRECT, rra);
ADD_INSTRUCTION(0x67, RRA, ZERO_PAGE, rra);
ADD_INSTRUCTION(0x6f, RRA, ABSOLUTE, rra);
ADD_INSTRUCTION(0x73, RRA, INDIRECT_INDEXED, rra);
ADD_INSTRUCTION(0x77, RRA, INDEXED_ZERO_PAGE_X, rra);
ADD_INSTRUCTION(0x7b, RRA, INDEXED_ABSOLUTE_Y, rra);
ADD_INSTRUCTION(0x7f, RRA, INDEXED_ABSOLUTE_X, rra);

