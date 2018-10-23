#include "tiles.h"

#define TILES_W 2
#define TILES_H 2

#define PAL3_TILEINDEX 0x01F0


#include "../base/screens_global.h"

void tiles_removeMapTile(s16 x, s16 y);
void tiles_addMapTile(u16 tile, s16 x, s16 y, u8 onTop);
void tiles_removeBackgroundTile(s16 x, s16 y);
void tiles_addBackgroundTile(u16 tile, s16 x, s16 y, u8 onTop);

void tiles_putMapTile(u16 tile, s16 x, s16 y, u8 onTop) {
	if (tile == 0) {
		tiles_removeMapTile(x, y);
	} else {
		tiles_addMapTile(tile * (TILES_W * TILES_H) + G_TILEINDEX_SUBFLOOR, x, y, onTop);
	}
}

void tiles_putBackgroundTile(u16 tile, s16 x, s16 y, u8 onTop) {
	if (tile == 0) {
		tiles_removeBackgroundTile(x, y);
	} else {
		tiles_addBackgroundTile(tile * (TILES_W * TILES_H) + G_TILEINDEX_SUBFLOOR, x, y, onTop);
	}
}

void tiles_removeMapTile(s16 x, s16 y) {
	s16 xx = x * TILES_W;
	s16 yy = y * TILES_H;
	s16 yy2 = yy + 1;
	s16 tile = 0x0;
	for (u16 i = 0; i < TILES_W; ++i) {
		u16 posX = xx + i;
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, FALSE, 0, 0, tile), posX, yy);
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, FALSE, 0, 0, tile), posX, yy2);
	}
}

void tiles_addMapTile(u16 tile, s16 x, s16 y, u8 onTop) {
	s16 xx = x * TILES_W;
	s16 yy = y * TILES_H;
	s16 yy2 = yy + 1;
	for (u16 i = 0; i < TILES_W; ++i) {
		u16 posX = xx + i;
		u16 tileI = tile + i;
		u16 tileI2 = tileI + TILES_W;
		u8 pal = tileI < PAL3_TILEINDEX ? PAL0 : PAL3;
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(pal, onTop, 0, 0, tileI),  posX, yy);
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(pal, onTop, 0, 0, tileI2), posX, yy2);
	}
}

void tiles_removeBackgroundTile(s16 x, s16 y) {
	s16 xx = x * TILES_W;
	s16 yy = y * TILES_H;
	s16 yy2 = yy + 1;
	for (u16 i = 0; i < TILES_W; ++i) {
		u16 posX = xx + i;
		u16 tile = G_TILEINDEX_SUBFLOOR + i;
		u16 tile2 = tile + TILES_W;
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL3, FALSE, 0, 0, tile), posX, yy);
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL3, FALSE, 0, 0, tile2), posX, yy2);
	}
}

void tiles_addBackgroundTile(u16 tile, s16 x, s16 y, u8 onTop) {
	s16 xx = x * TILES_W;
	s16 yy = y * TILES_H;
	s16 yy2 = yy + 1;
	for (u8 i = 0; i < TILES_W; ++i) {
		u8 posX = xx + i;
		u8 tileI = tile + i;
		u8 tileI2 = tileI + TILES_W;
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL0, onTop, 0, 0, tileI),  posX, yy);
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL0, onTop, 0, 0, tileI2), posX, yy2);
	}
}
