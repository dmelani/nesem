#pragma once

typedef struct {
	uint16_t pc;	// Program counter
	uint8_t a;	// Accumulator
	uint8_t x;	// Index X
	uint8_t y;	// Index Y
	uint8_t p;	// Flags
	uint8_t s;	// Stack pointer
} cpu;

cpu * cpu_create();
