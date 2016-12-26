#pragma once
#include <stdint.h>

#include "cartridge.h"

typedef struct mapper {
	uint8_t (*read)(struct mapper *mapper, uint16_t address);
	void (*write)(struct mapper *mapper, uint16_t address, uint8_t data);
	void (*destroy)(struct mapper *mapper);
} mapper;

mapper * mapper_create(cartridge *cartridge);
const char *mapper_type_name(uint8_t type);

mapper * mapper_nrom_create(cartridge *cartridge);
