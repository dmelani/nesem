#include <stdlib.h>
#include <stdio.h>

#include "mapper.h"
#include "cartridge.h"
#include "util.h"

typedef struct bank {
	uint16_t size;
	uint8_t *data;
} bank;

typedef struct nrom_mapper {
	mapper mapper;
	cartridge *cart;
	bank ram;
	bank lower;
	bank upper;
} nrom_mapper;

static uint8_t
read(mapper *mapper, uint16_t address) {
	nrom_mapper *nrom = (nrom_mapper *) mapper;

	if (address >= 0x6000 && address <= 0x7FFF) {
		if (nrom->ram.size == 0) {
			return 0;
		}
	} else if (address >= 0x8000 && address <= 0xBFFF) {
		return nrom->lower.data[address - 0x8000];
	} else if (address >= 0xC000 && address <= 0xFFFF) {
		return nrom->upper.data[address - 0xC000];
	}

	printf("Read from unmapped memory %x\n", address);
	return 0;
}

static void
write(mapper *mapper, uint16_t address, uint8_t data) {
	//nrom_mapper *nrom = (nrom_mapper *) mapper;
	return;
}

static void
destroy(mapper *mapper) {
	/* Don't free cart. Not owned by us. */
	nrom_mapper *nrom = (nrom_mapper *) mapper;

	printf("Destroying NROM mapper\n");
	free(nrom);
}

mapper *
mapper_nrom_create(cartridge *cart) {
	if (cart->no_rom_banks == 0) {
		printf("No rom banks! Cannot create NROM mapper");
		return NULL;
	}

	printf("Creating NROM mapper\n");
	nrom_mapper *nrom = xmalloc(sizeof(*nrom));	

	nrom->mapper.read = read;
	nrom->mapper.write = write;
	nrom->mapper.destroy = destroy;
	nrom->cart = cart;

	nrom->lower.data = nrom->cart->rom_banks[0];
	nrom->lower.size = ROM_BANK_SIZE;

	if (nrom->cart->no_rom_banks == 1) {
		/* Mirror lower bank if there is only 16KB of ROM */
		nrom->upper.data = nrom->lower.data;
		nrom->upper.size = nrom->lower.size;
	} else {
		nrom->upper.data = nrom->cart->rom_banks[1];
		nrom->upper.size = ROM_BANK_SIZE;
	}

	nrom->ram.data = NULL;
	nrom->ram.size = 0;

	return &nrom->mapper;
}
