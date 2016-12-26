#pragma once
#include <stdint.h>

typedef struct {
	uint8_t *mem;
	uint8_t (*read)(uint16_t address);
	void (*write)(uint16_t address, uint8_t data);
} mapper;

mapper * mapper_create(uint8_t type, uint8_t *memory);
const char *mapper_type_name(uint8_t type);

mapper * mapper_nrom_create(uint8_t *memory);
