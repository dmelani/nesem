#pragma once
#include "mapper.h"

#define TRAINER_SIZE 0x200
typedef char trainer[TRAINER_SIZE];

#define ROM_BANK_SIZE 0x4000
typedef char rom_bank[ROM_BANK_SIZE];

#define VROM_BANK_SIZE 0x2000
typedef char vrom_bank[VROM_BANK_SIZE];

typedef struct cartridge {
	char label[4];
	uint8_t no_rom_banks;
	uint8_t no_vrom_banks;
	uint8_t cb1;
	uint8_t cb2;
	uint8_t no_ram_banks;
	uint8_t pal;
	uint8_t zeros[6];
	trainer *trainer;
	rom_bank *rom_banks;
	vrom_bank *vrom_banks;
	mapper *mapper;
} cartridge;


cartridge *cartridge_load(const char *);
void cartridge_destroy(cartridge *);

