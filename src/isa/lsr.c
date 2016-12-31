#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
lsr(cpu *c, addressing_mode am) {
	uint8_t low = 0x00;
	uint16_t addr = 0x00;	
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
	printf("\tLSR: 0x%0.2x -> ", data);
	if (data & 0x01) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}
	data >>= 1;

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

ADD_INSTRUCTION(0x46, LSR, ZERO_PAGE, lsr);
ADD_INSTRUCTION(0x4a, LSR, ACCUMULATOR, lsr);
ADD_INSTRUCTION(0x4e, LSR, ABSOLUTE, lsr);
ADD_INSTRUCTION(0x56, LSR, INDEXED_ZERO_PAGE_X, lsr);
ADD_INSTRUCTION(0x5e, LSR, INDEXED_ABSOLUTE_X, lsr);
