#include "cpu.h"
#include "isa.h"
#include "linker_set.h"

static void
sei(cpu *c, addressing_mode am) {
	c->p |= CPU_FLAG_I;
	cpu_tick_clock(c); /* Takes one cycle more */
}

static instr i = {
	0x78,
	"SEI",
	IMPLIED,
	sei
};

LINKER_SET_ADD_DATA(ins, i);

