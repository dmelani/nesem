#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
sta(cpu *c, addressing_mode am) {
	printf("\tSTA: ");
	uint16_t addr = isa_load_write_addr(c, am);

	printf("A 0x%0.2x to addr 0x%0.4x\n", c->a, addr);
	cpu_write(c, addr, c->a);
}

ADD_INSTRUCTION(0x85, STA, ZERO_PAGE, sta);
ADD_INSTRUCTION(0x95, STA, INDEXED_ZERO_PAGE_X, sta);
ADD_INSTRUCTION(0x8d, STA, ABSOLUTE, sta);
ADD_INSTRUCTION(0x9d, STA, INDEXED_ABSOLUTE_X, sta);
ADD_INSTRUCTION(0x99, STA, INDEXED_ABSOLUTE_Y, sta);
ADD_INSTRUCTION(0x81, STA, INDEXED_INDIRECT, sta);
ADD_INSTRUCTION(0x91, STA, INDIRECT_INDEXED, sta);
