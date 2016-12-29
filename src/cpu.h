#pragma once
#include <stdint.h>
#include "isa/isa.h"
#include "mapper.h"

typedef struct cpu {
	uint64_t clock;	// Counter that keeps track of cycles
	uint16_t pc;	// Program counter
	uint8_t a;	// Accumulator
	uint8_t x;	// Index X
	uint8_t y;	// Index Y
	uint8_t s;	// Stack pointer

#define CPU_FLAG_C 1U << 0 // Carry
#define CPU_FLAG_Z 1U << 1 // Zero
#define CPU_FLAG_I 1U << 2 // Interrupt disable
#define CPU_FLAG_D 1U << 3 // Binary coded decimal
#define CPU_FLAG_B 1U << 4 // Breakpoint
#define CPU_FLAG_U 1U << 5 // Unused
#define CPU_FLAG_V 1U << 6 // Overflow
#define CPU_FLAG_N 1U << 7 // Sign
	uint8_t p;	// Flags

	uint8_t *mem;
	mapper *mapper;	

	instr **optable;
	size_t optable_size;
} cpu;

cpu * cpu_create(mapper *);
void cpu_destroy(cpu *);
void cpu_reset(cpu *);
void cpu_run(cpu *);
void cpu_tick_clock(cpu *);

uint8_t cpu_read(cpu *, uint16_t);
void cpu_write(cpu *, uint16_t, uint8_t);
void cpu_push(cpu *, uint8_t);
uint8_t cpu_pull(cpu *);
uint8_t cpu_advance(cpu *);
uint16_t cpu_read_paged_16(cpu *, uint16_t);
void cpu_set_z(cpu *, uint8_t);
void cpu_set_n(cpu *, uint8_t);
