#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
inc_zp(cpu *c, addressing_mode am) {
	uint8_t addr = cpu_advance(c);
	uint8_t data = cpu_read(c, addr);

	/*
	 * According to  http://nesdev.com/6502_cpu.txt:
	 * Read-Modify-Write instructions write unmodified data, then modified
	 * (so INC effectively does LDX loc;STX loc;INX;STX loc)
	 */

	printf("\tINC (0x00%0.2x): 0x%0.2x ", addr, data);
	cpu_write(c, addr, data++);
	printf("to 0x%0.2x\n", data);

	cpu_set_z(c, data);
	cpu_set_n(c, data);

	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0xe6, INC, ZERO_PAGE, inc_zp);

