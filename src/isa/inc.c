#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
inc_zp(cpu *c, addressing_mode am) {
	uint8_t addr = cpu_advance(c);
	uint8_t data = cpu_read(c, addr);

	/*
	 * According to  http://nesdev.com/6502_cpu.txt the cpu writes back to
	 * memory while it does the operation on the read data and then writes
	 * the result to the same spot. Not sure if this is correct... 
	 */

	printf("\tINC (0x00%0.2x): 0x%0.2x ", addr, data);
	cpu_write(c, addr, data++);
	printf("to 0x%0.2x\n", data);

	c->p &= ~CPU_FLAG_N; // Clear N flag
	c->p |= data & CPU_FLAG_N; // Set N flag if x >= 128
	if (data == 0) {
		c->p |= CPU_FLAG_Z;
	} else {
		c->p &= ~CPU_FLAG_Z;
	}

	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0xe6, inc, ZERO_PAGE, inc_zp);

