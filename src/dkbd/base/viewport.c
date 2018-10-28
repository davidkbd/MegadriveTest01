#include "viewport.h"

#include "../util/limits.h"
#include "../util/vector2.h"
#include "../util/rect.h"
#include "../util/tiles.h"
#include "../util/map.h"

#define VIEWPORT_TILEWIDTH 16
#define VIEWPORT_TILEHEIGHT 16
#define VIEWPORT_WIDTH 320
#define VIEWPORT_HEIGHT 224

#define VIEWPORT_HSCROLL_LINES_SIZE 256

/**
 * Datos del viewport
 */
struct Viewport_DATA_st {
	// Scroll
	Vector2 rawPosition;
	Vector2 realPosition;
	// Tiles
	Rect lastPosition;
	Rect currentPosition;
	// Dibujado de tiles central
	Vector2 lastCenterTilesPosition;
	// Scroll data
	s16 hzScrollLinesPlanA[VIEWPORT_HSCROLL_LINES_SIZE];
	s16 hzScrollLinesPlanB[VIEWPORT_HSCROLL_LINES_SIZE];
} Viewport_DATA;

void viewport_fillOfTiles();
void viewport_putColumnOfTiles(s16 x);
void viewport_putRowOfTiles(s16 y);
void viewport_putPlanATile(s16 x, s16 y);
void viewport_putPlanBTile(s16 x, s16 y);
void viewport_putRectOfTiles(s16 x1, s16 x2, s16 miny, s16 maxy);
void viewport_updatePlanATile(s16 x, s16 y);
u8 viewport_isMovingUp();
u8 viewport_isMovingDown();
u8 viewport_isMovingLeft();
u8 viewport_isMovingRight();
u8 viewport_isCenterTilesUpdateNeeded();
void viewport_calculateRealXPosition();
void viewport_calculateRealYPosition();
void viewport_calculateCurrentXPosition();
void viewport_calculateCurrentYPosition();
void viewport_drawXTiles();
void viewport_drawYTiles();
void viewport_drawCenterTiles();
void viewport_updateLastXPosition();
void viewport_updateLastYPosition();
void viewport_updateLastCenterTilesPosition();
void viewport_vdpSetHorizontalScroll();
void viewport_vdpSetVerticalScroll();

void viewport_reset(s16 x, s16 y) {
	Viewport_DATA.rawPosition.x = x;
	Viewport_DATA.rawPosition.y = y;

	Viewport_DATA.lastCenterTilesPosition.x = x; // Para que drawCenterTiles pinte porque x es raw, lastCenterTilesPosition es current
	Viewport_DATA.lastCenterTilesPosition.y = y; // Para que drawCenterTiles pinte porque y es raw, lastCenterTilesPosition es current

	viewport_calculateRealXPosition();
	viewport_calculateCurrentXPosition();
	viewport_calculateRealYPosition();
	viewport_calculateCurrentYPosition();

	viewport_fillOfTiles();
	viewport_drawCenterTiles();

	viewport_updateLastXPosition();
	viewport_updateLastYPosition();

	viewport_vdpSetHorizontalScroll();
	viewport_vdpSetVerticalScroll();
}

void viewport_moveX(s16 x) {
	Viewport_DATA.rawPosition.x += limits_s16(x, -60, 60);

	viewport_calculateRealXPosition();
	viewport_calculateCurrentXPosition();
	viewport_drawXTiles();
	viewport_drawCenterTiles();
	viewport_updateLastXPosition();
	viewport_vdpSetHorizontalScroll();
}

void viewport_moveY(s16 y) {
	Viewport_DATA.rawPosition.y += limits_s16(y, -60, 60);

	viewport_calculateRealYPosition();
	viewport_calculateCurrentYPosition();
	viewport_drawYTiles();
	viewport_drawCenterTiles();
	viewport_updateLastYPosition();
	viewport_vdpSetVerticalScroll();
}

s16 viewport_getCurrentX() {
	return Viewport_DATA.rawPosition.x;
}

s16 viewport_getCurrentY() {
	return Viewport_DATA.rawPosition.y;
}

void viewport_putRectOfTiles(s16 minx, s16 maxx, s16 miny, s16 maxy) {
	for (s16 x = minx; x <= maxx; ++x) {
		for (s16 y = miny; y <= maxy; ++y) {
			viewport_updatePlanATile(x, y);
		}
	}
}

void viewport_updatePlanATile(s16 x, s16 y) {/*
	u16 tileId = map_getPlanA(x, y);
	if (tileId > 26) {
		s16 realY = map_getOnTop(tileId) + Viewport_DATA.currentPosition.pos1.y;
		u8 onTop = y > realY;
		tiles_putMapTile(tileId, x, y, onTop);
	}*/
}

void viewport_fillOfTiles() {
	for (s16 i = Viewport_DATA.currentPosition.pos1.x; i <= Viewport_DATA.currentPosition.pos2.x; ++i) {
		viewport_putColumnOfTiles(i);
	}
}

void viewport_putColumnOfTiles(s16 x) {
	for (s16 y = Viewport_DATA.currentPosition.pos1.y; y <= Viewport_DATA.currentPosition.pos2.y; ++y) {
		viewport_putPlanATile(x, y);
	}
}

void viewport_putRowOfTiles(s16 y) {
	for (s16 x = Viewport_DATA.currentPosition.pos1.x; x <= Viewport_DATA.currentPosition.pos2.x; ++x) {
		viewport_putPlanATile(x, y);
	}
}

void viewport_putPlanATile(s16 x, s16 y) {
	u16 tileId = map_getPlanA(x, y);
	tiles_putMapTile(tileId, x, y, FALSE);
}

void viewport_putPlanBTile(s16 x, s16 y) {
	u16 tileId = map_getPlanB(x, y);
	tiles_putBackgroundTile(tileId, x, y, FALSE);
}

u8 viewport_isMovingUp() {
	return Viewport_DATA.currentPosition.pos1.y < Viewport_DATA.lastPosition.pos1.y;
}

u8 viewport_isMovingDown() {
	return Viewport_DATA.currentPosition.pos2.y > Viewport_DATA.lastPosition.pos2.y;
}

u8 viewport_isMovingLeft() {
	return Viewport_DATA.currentPosition.pos1.x < Viewport_DATA.lastPosition.pos1.x;
}

u8 viewport_isMovingRight() {
	return Viewport_DATA.currentPosition.pos2.x > Viewport_DATA.lastPosition.pos2.x;
}

u8 viewport_isCenterTilesUpdateNeeded() {
	return Viewport_DATA.lastCenterTilesPosition.x != Viewport_DATA.currentPosition.pos1.x || Viewport_DATA.lastCenterTilesPosition.y != Viewport_DATA.currentPosition.pos1.y;
}

void viewport_calculateRealXPosition() {
	Viewport_DATA.realPosition.x = Viewport_DATA.rawPosition.x / 10;
}

void viewport_calculateRealYPosition() {
	Viewport_DATA.realPosition.y = Viewport_DATA.rawPosition.y / 10;
}

void viewport_calculateCurrentXPosition() {
	Viewport_DATA.currentPosition.pos1.x = -((Viewport_DATA.realPosition.x + VIEWPORT_TILEWIDTH) / VIEWPORT_TILEWIDTH);
	Viewport_DATA.currentPosition.pos2.x = -((Viewport_DATA.realPosition.x - VIEWPORT_WIDTH)     / VIEWPORT_TILEWIDTH);
}

void viewport_calculateCurrentYPosition() {
	Viewport_DATA.currentPosition.pos1.y = (Viewport_DATA.realPosition.y - VIEWPORT_TILEHEIGHT) / VIEWPORT_TILEHEIGHT;
	Viewport_DATA.currentPosition.pos2.y = (Viewport_DATA.realPosition.y + VIEWPORT_HEIGHT)     / VIEWPORT_TILEHEIGHT;
}

void viewport_drawXTiles() {
	if (viewport_isMovingLeft()) {
		viewport_putColumnOfTiles(Viewport_DATA.currentPosition.pos1.x);
	}
	if (viewport_isMovingRight()) {
		viewport_putColumnOfTiles(Viewport_DATA.currentPosition.pos2.x);
	}
}

void viewport_drawYTiles() {
	if (viewport_isMovingUp()) {
		viewport_putRowOfTiles(Viewport_DATA.currentPosition.pos1.y);
	}
	if (viewport_isMovingDown()) {
		viewport_putRowOfTiles(Viewport_DATA.currentPosition.pos2.y);
	}
}

void viewport_drawCenterTiles() {
	if (viewport_isCenterTilesUpdateNeeded()) {
		viewport_putRectOfTiles(
				Viewport_DATA.currentPosition.pos1.x + 8,
				Viewport_DATA.currentPosition.pos2.x - 9,
				Viewport_DATA.currentPosition.pos1.y + 4,
				Viewport_DATA.currentPosition.pos2.y - 6);
		viewport_updateLastCenterTilesPosition();
	}
}

void viewport_updateLastXPosition() {
	Viewport_DATA.lastPosition.pos1.x = Viewport_DATA.currentPosition.pos1.x;
	Viewport_DATA.lastPosition.pos2.x = Viewport_DATA.currentPosition.pos2.x;
}

void viewport_updateLastYPosition() {
	Viewport_DATA.lastPosition.pos1.y = Viewport_DATA.currentPosition.pos1.y;
	Viewport_DATA.lastPosition.pos2.y = Viewport_DATA.currentPosition.pos2.y;
}

void viewport_updateLastCenterTilesPosition() {
	Viewport_DATA.lastCenterTilesPosition.x = Viewport_DATA.currentPosition.pos1.x;
	Viewport_DATA.lastCenterTilesPosition.y = Viewport_DATA.currentPosition.pos1.y;
}

void viewport_vdpSetHorizontalScroll() {
	s16 yPosition = Viewport_DATA.rawPosition.y / 300;
	s16 linelimit = 160 - yPosition;
	const s16 planbPos = Viewport_DATA.rawPosition.x / 20;
	u16 line = 0;
	while (line < linelimit) {
		Viewport_DATA.hzScrollLinesPlanA[line] = Viewport_DATA.realPosition.x;
		Viewport_DATA.hzScrollLinesPlanB[line] = planbPos;
		 ++line;
	}
	u16 displacedLine = 1;
	while (line < VIEWPORT_HSCROLL_LINES_SIZE) {
		s16 y = (Viewport_DATA.realPosition.x * displacedLine) / 80 + planbPos;
		Viewport_DATA.hzScrollLinesPlanA[line] = Viewport_DATA.realPosition.x;
		Viewport_DATA.hzScrollLinesPlanB[line] = y;
		++line;
		++displacedLine;
	}
	VDP_setHorizontalScrollLine(PLAN_A, 0, Viewport_DATA.hzScrollLinesPlanA, VIEWPORT_HSCROLL_LINES_SIZE, TRUE);
	VDP_setHorizontalScrollLine(PLAN_B, 0, Viewport_DATA.hzScrollLinesPlanB, VIEWPORT_HSCROLL_LINES_SIZE, TRUE);
}

void viewport_vdpSetVerticalScroll() {
	VDP_setVerticalScroll(PLAN_A, Viewport_DATA.realPosition.y);
	VDP_setVerticalScroll(PLAN_B, Viewport_DATA.rawPosition.y / 300);
}
