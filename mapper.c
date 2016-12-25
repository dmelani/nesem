#include "util.h"
#include "mapper.h"

mapper *
mapper_create(uint8_t *memory) {
	mapper *map = xmalloc(sizeof(*map));
	map->mem = memory;

	return map;
}


