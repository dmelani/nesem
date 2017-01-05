#include <stdio.h>

#include "cpu.h"
#include "isa.h"

static void
isc(cpu *c, addressing_mode am) {
	printf("\tISC: ");
	uint16_t addr = isa_load_read_write_addr(c, am);
	uint8_t data = cpu_read(c, addr);

	printf("(0x%0.4x) 0x%0.2x ", addr, data);
	cpu_write(c, addr, data++);

	uint8_t carry = c->p & CPU_FLAG_C;
	uint16_t tmp = c->a - data - (carry ? 0 : 1);

	cpu_set_n(c, tmp & 0xFF);
	cpu_set_z(c, tmp & 0xFF);

	if (((c->a ^ tmp) & 0x80) && ((c->a ^ data) & 0x80)) {
		c->p |= CPU_FLAG_V;
	} else {
		c->p &= ~CPU_FLAG_V;
	}

	if (tmp < 0x100) {
		c->p |= CPU_FLAG_C;
	} else {
		c->p &= ~CPU_FLAG_C;
	}

	c->a = tmp & 0xFF;

	printf("to 0x%0.2x and cmp with 0x%0.2x Flags: 0x%0.2x\n", data, c->a, c->p);
	cpu_write(c, addr, data);
}

ADD_INSTRUCTION(0xe3, ISC, INDEXED_INDIRECT, isc);
ADD_INSTRUCTION(0xe7, ISC, ZERO_PAGE, isc);
ADD_INSTRUCTION(0xef, ISC, ABSOLUTE, isc);
ADD_INSTRUCTION(0xf3, ISC, INDIRECT_INDEXED, isc);
ADD_INSTRUCTION(0xf7, ISC, INDEXED_ZERO_PAGE_X, isc);
ADD_INSTRUCTION(0xfb, ISC, INDEXED_ABSOLUTE_Y, isc);
ADD_INSTRUCTION(0xff, ISC, INDEXED_ABSOLUTE_X, isc);

