#include "map.h"

#include "map_restriction.h"
#include "map_ontop.h"

#include "string.h"
#include "limits.h"

#define MAP_PLAN_A 0

void map_loadMap(u8 plan, const u8 * (*map)[MAP_WIDTH]);
u8 map_get(u8 plan, u8 x, u8 y);
u8 map_calculateWidth();
u8 map_calculateHeight();

struct Map_DATA_st {
	const u8 (*data)[MAP_WIDTH];
	u8 width;
	u8 height;
} *Map_DATA = NULL;

void map_load(const u8 * (*mapPlanA)[MAP_WIDTH]) {
	map_destroy();
	Map_DATA = MEM_alloc(sizeof(struct Map_DATA_st) * 1);
	map_loadMap(MAP_PLAN_A, mapPlanA);
	Map_DATA[MAP_PLAN_A].width = map_calculateWidth();
	Map_DATA[MAP_PLAN_A].height = map_calculateHeight();
}

void map_destroy() {
	if (Map_DATA != NULL) {
		MEM_free(Map_DATA);
	}
}

u8 map_getWidth() {
	return Map_DATA[MAP_PLAN_A].width;
}

u8 map_getHeight() {
	return Map_DATA[MAP_PLAN_A].height;
}

u8 map_getPlanA(u8 x, u8 y) {
	return map_get(MAP_PLAN_A, x, y);
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

void map_loadMap(u8 plan, const u8 * (*map)[MAP_WIDTH]) {
	Map_DATA[plan].data = &(map[0][0]);
}

u8 map_get(u8 plan, u8 x, u8 y) {
	u16 xx = limits_cycle_s16(x, 0, 0, map_getWidth());
	u16 yy = limits_cycle_s16(y, 0, 0, map_getHeight());
	return Map_DATA[plan].data[yy][xx];
}

u8 map_calculateWidth() {
	for (u8 x = 0; x < MAP_WIDTH; ++x) {
		if (Map_DATA[MAP_PLAN_A].data[0][x] == 127) {
			return x + 1;
		}
	}
	return MAP_WIDTH;
}

u8 map_calculateHeight() {
	for (u8 y = 0; y < MAP_HEIGHT; ++y) {
		if (Map_DATA[MAP_PLAN_A].data[y][0] == 127) {
			return y + 1;
		}
	}
	return MAP_HEIGHT;
}
