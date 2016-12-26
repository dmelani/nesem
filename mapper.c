#include "util.h"
#include "mapper.h"

/* XXX - User linker sets here instead */
const struct mapper_types {
	uint8_t type;
	char *name;
	mapper *(*create)(uint8_t *memory);
} MAPPER_TYPES[] = {
	{0, "No mapper", mapper_nrom_create},
	{1, "Nintendo MMC1", NULL},
	{2, "CNROM switch", NULL},
	{3, "UNROM switch", NULL},
	{4, "Nintendo MMC3", NULL},
	{5, "Nintendo MMC5", NULL},
	{6, "FFE F4xxx", NULL},
	{7, "AOROM switch", NULL},
	{8, "FFE F3xxx", NULL},
	{9, "Nintendo MMC2", NULL},
	{10, "Nintendo MMC4", NULL},
	{11, "ColorDreams chip", NULL},
	{12, "FFE F6xxx", NULL},
	{13, "CPROM switch", NULL},
	{15, "100-in-1 switch", NULL},
	{16, "Bandai chip", NULL},
	{17, "FFE F8xxx", NULL},
	{18, "Jaleco SS8806 chip", NULL},
	{19, "Namcot 106 chip", NULL},
	{20, "Nintendo DiskSystem", NULL},
	{21, "Konami VRC4a", NULL},
	{22, "Konami VRC2a", NULL},
	{23, "Konami VRC2a", NULL},
	{24, "Konami VRC6", NULL},
	{25, "Konami VRC4b", NULL},
	{32, "Irem G-101 chip", NULL},
	{33, "Taito TC0190/TC0350", NULL},
	{34, "Nina-1 board", NULL},
	{64, "Tengen RAMBO-1 chip", NULL},
	{65, "Irem H-3001 chip", NULL},
	{66, "GNROM switch", NULL},
	{67, "SunSoft3 chip", NULL},
	{68, "SunSoft4 chip", NULL},
	{69, "SunSoft5 FME-7 chip", NULL},
	{71, "Camerica chip", NULL},
	{78, "Irem 74HC161/32-based", NULL},
	{79, "AVE Nina-3 board", NULL},
	{81, "AVE Nina-6 board", NULL},
	{91, "Pirate HK-SF3 chip", NULL},
	{0xFF, "Unknown", NULL},
};

mapper *
mapper_create(uint8_t type, uint8_t *memory) {
	for (const struct mapper_types *mpt = MAPPER_TYPES; mpt->type != 0xFF; mpt++) {
		if (mpt->type == type) {
			if (mpt->create == NULL) {
				printf("Mapper type %s not implemented\n", mpt->name);
				return NULL;
			}

			return mpt->create(memory);
		}
	}

	return NULL;
}

const char *
mapper_type_name(uint8_t type) {
	const struct mapper_types *cur = NULL;
	for(cur = MAPPER_TYPES; type != cur->type && cur->type != 0xff; cur++);
	return cur->name;
}
