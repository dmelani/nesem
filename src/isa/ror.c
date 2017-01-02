#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
ror(cpu *c, addressing_mode am) {
	printf("\tROR: ");
	uint16_t addr = isa_load_write_addr(c);	
	uint8_t prev = c->p;
	uint8_t data;
	
	/* Load */
	if (am == ACCUMULATOR) {
			cpu_read(c, c->pc);
			data = c->a;
	}
	/* Op */
	printf("0x%0.2x -> ", data);

	if (data & 0x01) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	data >>= 1;
	if (prev & CPU_FLAG_C)
		data |= 1 << 7;

	cpu_set_n(c, data);
	cpu_set_z(c, data);

	/* Store */
	switch (am) {
		case ACCUMULATOR:
			c->a = data;
			break;
		case ABSOLUTE:
			cpu_write(c, addr, data);
			break;
		case INDEXED_ABSOLUTE_X:
			cpu_write(c, addr, data);
			break;
		case ZERO_PAGE:
			cpu_write(c, low, data);
			break;
		case INDEXED_ZERO_PAGE_X:
			cpu_write(c, low, data);
			break;
		default:
			printf("UNHANDLED ADDRESSING MODE\n");
			return;
	}

	printf("0x%0.2x Flags: 0x%0.2x\n", data, c->p);
}

ADD_INSTRUCTION(0x66, ROR, ZERO_PAGE, ror);
ADD_INSTRUCTION(0x6a, ROR, ACCUMULATOR, ror);
ADD_INSTRUCTION(0x6e, ROR, ABSOLUTE, ror);
ADD_INSTRUCTION(0x76, ROR, INDEXED_ZERO_PAGE_X, ror);
ADD_INSTRUCTION(0x7e, ROR, INDEXED_ABSOLUTE_X, ror);
