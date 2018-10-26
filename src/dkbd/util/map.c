#include "map.h"

#include "map_restriction.h"
#include "map_ontop.h"

#include "string.h"
#include "limits.h"

#define MAP_PLAN_A 1
#define MAP_PLAN_B 0

#include "../maps/level01_b.h"

void map_loadMap(u8 plan, const u8 * (*map)[MAP_SIZE]);
u8 map_get(u8 plan, u8 x, u8 y);

struct Map_DATA_st {
	const u8 (*data)[MAP_SIZE];
} *Map_DATA = NULL;

void map_load(const u8 * (*mapPlanB)[MAP_SIZE], const u8 * (*mapPlanA)[MAP_SIZE]) {
	map_destroy();
	Map_DATA = MEM_alloc(sizeof(struct Map_DATA_st) * 2);
	map_loadMap(MAP_PLAN_B, mapPlanB);
	map_loadMap(MAP_PLAN_A, mapPlanA);
}

void map_destroy() {
	if (Map_DATA != NULL) {
		MEM_free(Map_DATA);
	}
}

u8 map_getWidth() {
	return MAP_SIZE;
}

u8 map_getHeight() {
	return MAP_SIZE;
}

u8 map_getPlanA(u8 x, u8 y) {
	return map_get(MAP_PLAN_A, x, y);
}

u8 map_getPlanB(u8 x, u8 y) {
	return map_get(MAP_PLAN_B, x, y);
}

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

void map_loadMap(u8 plan, const u8 * (*map)[MAP_SIZE]) {
	Map_DATA[plan].data = &(map[0][0]);
}

u8 map_get(u8 plan, u8 x, u8 y) {
	u16 xx = limits_cycle_s16(x, 0, 0, map_getWidth());
	u16 yy = limits_cycle_s16(y, 0, 0, map_getHeight());
	return Map_DATA[plan].data[yy][xx];
}
