#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sta(cpu *c, addressing_mode am) {
	uint8_t low = cpu_advance(c);
	uint8_t high = cpu_advance(c);
	uint16_t addr = low | (high << 8);

	printf("\tSTA: A 0x%0.2x to addr 0x%0.4x\n", c->a, addr);

	cpu_write(c, addr, c->a);
}

static void
sta_indirect_indexed(cpu *c, addressing_mode am) {
	uint8_t zpa = cpu_advance(c);
	uint16_t addr = cpu_read(c, zpa);
	addr += c->y;
	cpu_tick_clock(c); /* Takes one cycle more */

	printf("\tSTA (0x%0.2x),0x%0.2x: A 0x%0.2x to addr 0x%0.4x\n", zpa, c->y, c->a, addr);
	cpu_write(c, addr, c->a);
	cpu_tick_clock(c); /* Takes one cycle more */
}

ADD_INSTRUCTION(0x8d, STA, ABSOLUTE, sta);
ADD_INSTRUCTION(0x91, STA, INDIRECT_INDEXED, sta_indirect_indexed);

