#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
ror(cpu *c, addressing_mode am) {
	uint8_t low = 0x00;
	uint16_t addr = 0x00;	
	uint8_t prev = c->p;
	uint8_t data;
	
	/* Load */
	switch (am) {
		case ACCUMULATOR:
			data = c->a;
	 		break;
		case ABSOLUTE:
			low = cpu_advance(c); 
			addr = low | (cpu_advance(c) << 8);

			data = cpu_read(c, addr);
			cpu_write(c, addr, data);

			break;
		case ZERO_PAGE:
			low = cpu_advance(c); 

			data = cpu_read(c, low);
			cpu_write(c, low, data);

			break;
		case INDEXED_ZERO_PAGE_X:
			low = cpu_advance(c); 

			cpu_read(c, low); // According to http://nesdev.com/6502_cpu.txt
			low += c->x;

			data = cpu_read(c, low);
			cpu_write(c, low, data);

			break;
		case INDEXED_ABSOLUTE_X:
			low = cpu_advance(c); 
			uint8_t high = cpu_advance(c);
			low += c->x;

			addr = low;
			addr |= (high << 8);
			cpu_read(c, addr); // According to http://nesdev.com/6502_cpu.txt this can happen before the previous step

			data = cpu_read(c, addr);
			cpu_write(c, addr, data); // According to http://nesdev.com/6502_cpu.txt

			break;
		default:
			printf("UNHANDLED ADDRESSING MODE\n");
			return;
	}

	/* Op */
	printf("\tROR: 0x%0.2x -> ", data);

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
			cpu_tick_clock(c);
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
