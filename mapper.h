#pragma once
#include <stdint.h>

typedef struct {
	uint8_t *mem;
} mapper;

mapper * mapper_create(uint8_t *memory);
uint8_t mapper_read(uint16_t address);
const char *mapper_type_name(uint8_t type);
