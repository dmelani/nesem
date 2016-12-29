#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
bit(cpu *c, addressing_mode am) {
	uint8_t data;
	uint8_t low = cpu_advance(c);
	uint16_t addr = low;
	
	if (am == ABSOLUTE)
		addr = low | (cpu_advance(c) << 8);

	data = cpu_read(c, addr);
	
	cpu_set_z(c, c->a & data);
	
	// Clear N and V flags
	c->p &= ~(CPU_FLAG_N | CPU_FLAG_V);

	// Copy flags from data at addr
	c->p |= data & (CPU_FLAG_N | CPU_FLAG_V);

	printf("\tBIT (0x%0.4x): 0x%0.2x Flags: 0x%0.2x\n", addr, data, c->p);
}

ADD_INSTRUCTION(0x24, BIT, ZERO_PAGE, bit);
ADD_INSTRUCTION(0x2c, BIT, ABSOLUTE, bit);

