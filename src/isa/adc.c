#include <stdio.h>

#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
adc(cpu *c, addressing_mode am) {
	uint8_t data = cpu_advance(c);
	uint8_t carry = c->p & CPU_FLAG_C;

	if (am == ZERO_PAGE) {
		data = cpu_read(c, data);
	}

	uint16_t tmp = c->a + data + (carry ? 1 : 0);

	printf("\tADC: 0x%0.2x + 0x%0.2x + 0x%0.1x = ", c->a, data, carry ? 1 : 0);

	cpu_set_n(c, tmp & 0xFF);
	cpu_set_z(c, tmp & 0xFF);

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
	printf("0x%0.2x Flags: 0x%0.2x\n",  c->a, c->p);
}

ADD_INSTRUCTION(0x69, ADC, IMMEDIATE, adc);
ADD_INSTRUCTION(0x65, ADC, ZERO_PAGE, adc);

