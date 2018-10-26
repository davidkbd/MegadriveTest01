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
		u8 n = TILES_W * TILES_H;
		tiles_addMapTile(tile * n + G_TILEINDEX_MAP, x, y, onTop);
	}
}

void tiles_putBackgroundTile(u16 tile, s16 x, s16 y, u8 onTop) {
	if (tile == 0) {
		tiles_removeBackgroundTile(x, y);
	} else {
		u8 n = TILES_W * TILES_H;
		tiles_addBackgroundTile(tile * n + G_TILEINDEX_MAP, x, y, onTop);
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
	s16 posX = x * TILES_W;
	s16 yy = y * TILES_H;
	s16 yy2 = yy + 1;
	for (u16 i = 0; i < TILES_W; ++i) {
		u16 tileI = tile + i;
		u16 tileI2 = tileI + TILES_W;
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, onTop, 0, 0, tileI),  posX, yy);
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, onTop, 0, 0, tileI2), posX, yy2);
		++posX;
	}
}

void tiles_removeBackgroundTile(s16 x, s16 y) {
	s16 posX = x * TILES_W;
	s16 yy = y * TILES_H;
	s16 yy2 = yy + 1;
	u16 tile = 0x0;
	for (u16 i = 0; i < TILES_W; ++i) {
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL3, FALSE, 0, 0, tile), posX, yy);
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL3, FALSE, 0, 0, tile), posX, yy2);
		++posX;
	}
}

void tiles_addBackgroundTile(u16 tile, s16 x, s16 y, u8 onTop) {
	s16 posX = x * TILES_W;
	s16 yy = y * TILES_H;
	s16 yy2 = yy + 1;
	for (u8 i = 0; i < TILES_W; ++i) {
		u8 tileI = tile + i;
		u8 tileI2 = tileI + TILES_W;
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL3, onTop, 0, 0, tileI),  posX, yy);
		VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL3, onTop, 0, 0, tileI2), posX, yy2);
		++posX;
	}
}
