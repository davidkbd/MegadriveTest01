#include "map.h"

#include "map_restriction.h"
#include "map_ontop.h"

#include "string.h"
#include "limits.h"

u8 map_calculateWidth();
u8 map_calculateHeight();

struct Map_DATA_st {
	const u8 (*data)[MAP_WIDTH];
	const u8 (*sprites)[MAP_WIDTH];
	u8 width;
	u8 height;
} *Map_DATA = NULL;

void map_load(const u8 * (*mapPlanA)[MAP_WIDTH], const u8 * (*sprites)[MAP_WIDTH]) {
	map_destroy();
	Map_DATA = MEM_alloc(sizeof(struct Map_DATA_st) * 1);
	Map_DATA->data = &(mapPlanA[0][0]);
	Map_DATA->sprites = &(sprites[0][0]);
	Map_DATA->width = map_calculateWidth();
	Map_DATA->height = map_calculateHeight();
}

void map_destroy() {
	if (Map_DATA != NULL) {
		MEM_free(Map_DATA);
	}
}

u8 map_getWidth() {
	return Map_DATA->width;
}

u8 map_getHeight() {
	return Map_DATA->height;
}

u8 map_getPlanA(u8 x, u8 y) {
	return Map_DATA->data[y][x];
}

u8 map_getSprite(u8 x, u8 y) {
	u8 s = Map_DATA->sprites[y][x];
	if (s < 160) {
		return 0;
	}
	return s - 160;
}

//u8 map_getPlanB(u8 x, u8 y) {
//	return map_get(MAP_PLAN_B, x, y);
//}

u16 map_getRestriction(u8 x, u8 y) {
	u16 m = map_getPlanA(x, y);
	if (m < MAP_RESTRICTION_COUNT) {
		return map_restrictions[m];
	}
	return 0;
}

u8 map_getOnTop(u8 tileId) {
	return map_ontop[tileId];
}

u8 map_calculateWidth() {
	for (u8 x = 0; x < MAP_WIDTH; ++x) {
		if (Map_DATA->data[0][x] == MAP_END_ITEM) {
			return x + 1;
		}
	}
	return MAP_WIDTH;
}

u8 map_calculateHeight() {
	for (u8 y = 0; y < MAP_HEIGHT; ++y) {
		if (Map_DATA->data[y][0] == MAP_END_ITEM) {
			return y + 1;
		}
	}
	return MAP_HEIGHT;
}
