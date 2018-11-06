#include "viewport.h"

#include "screens_global.h"
#include "../util/limits.h"
#include "../util/vector2.h"
#include "../util/rect.h"
#include "../util/tiles.h"
#include "../util/map.h"
#include "../util/math.h"

#include "../../../res/gfx.h"

#define VIEWPORT_TILEWIDTH 16
#define VIEWPORT_TILEHEIGHT 16
#define VIEWPORT_WIDTH 320
#define VIEWPORT_HEIGHT 224

#define VIEWPORT_MAX_LEFT_SPEED  -60
#define VIEWPORT_MAX_RIGHT_SPEED  60
#define VIEWPORT_MAX_UP_SPEED    -60
#define VIEWPORT_MAX_DOWN_SPEED   60

#define VIEWPORT_HSCROLL_LINES_SIZE 224

// 3dfx
#define VIEWPORT_OCEAN_LINE 160

/**
 * Datos del viewport
 */
struct Viewport_DATA_st {
	u8 pausa;
	// Scroll
	Vector2 rawPosition;
	Vector2 planAPosition;
	Vector2 planBPosition;
	Rect limits;
	// Tiles
	Rect lastPositionInTiles;
	Rect currentPositionInTiles;
	// Scroll data
	s16 hzScrollLinesPlanA[VIEWPORT_HSCROLL_LINES_SIZE];
	s16 hzScrollLinesPlanB[VIEWPORT_HSCROLL_LINES_SIZE];
	// Cuando al hacer scroll aparece un sprite, se llama al callback
	void (*onSpriteReplaceCallback)(u8 spriteId, s16 x, s16 y);
	void (*callback3dfxPtr)();
} * Viewport_DATA;

void viewport_refreshColumn(s16 x);
void viewport_refreshRow(s16 y);
void viewport_putPlanATile(s16 x, s16 y);
void viewport_putSprite(s16 x, s16 y);
u8 viewport_isMovingUp();
u8 viewport_isMovingDown();
u8 viewport_isMovingLeft();
u8 viewport_isMovingRight();
void viewport_calculatePlanAXPosition();
void viewport_calculatePlanAYPosition();
void viewport_calculatePlanBXPosition();
void viewport_calculatePlanBYPosition();
void viewport_calculateCurrentXPosition();
void viewport_calculateCurrentYPosition();
void viewport_drawXTiles();
void viewport_drawYTiles();
void viewport_updateLastXPosition();
void viewport_updateLastYPosition();
void viewport_vint();
void viewport_ocean3dfx();


void viewport_initialize(const Vector2 *initialPoisition, Rect limits, void (*callback)(u8 spriteId, s16 x, s16 y)) {
	Viewport_DATA = MEM_alloc(sizeof(struct Viewport_DATA_st));

	s16 *arrA = Viewport_DATA->hzScrollLinesPlanA;
	s16 *arrB = Viewport_DATA->hzScrollLinesPlanB;
	for (u8 line = 0; line < VIEWPORT_HSCROLL_LINES_SIZE; ++line) {
		arrA[line] = 0;
		arrB[line] = 0;
	}

	Viewport_DATA->pausa = FALSE;
	Viewport_DATA->onSpriteReplaceCallback = callback;
	Viewport_DATA->callback3dfxPtr = viewport_ocean3dfx;
	Viewport_DATA->limits.pos1.x = -limits.pos1.x;
	Viewport_DATA->limits.pos2.x = -limits.pos2.x;
	Viewport_DATA->limits.pos1.y = limits.pos1.y;
	Viewport_DATA->limits.pos2.y = limits.pos2.y;
	Viewport_DATA->rawPosition.x = -(initialPoisition->x - VIEWPORT_WIDTH * 5);
	Viewport_DATA->rawPosition.y = initialPoisition->y - VIEWPORT_HEIGHT * 5;
	Viewport_DATA->rawPosition.x = limits_s16(Viewport_DATA->rawPosition.x, Viewport_DATA->limits.pos2.x, Viewport_DATA->limits.pos1.x);
	Viewport_DATA->rawPosition.y = limits_s16(Viewport_DATA->rawPosition.y, Viewport_DATA->limits.pos1.y, Viewport_DATA->limits.pos2.y);

	viewport_calculatePlanAXPosition();
	viewport_calculatePlanBXPosition();
	viewport_calculateCurrentXPosition();
	viewport_calculatePlanAYPosition();
	viewport_calculatePlanBYPosition();
	viewport_calculateCurrentYPosition();
	viewport_refreshCurrentViewport();

	viewport_updateLastXPosition();
	viewport_updateLastYPosition();
	Viewport_DATA->callback3dfxPtr();

	SYS_enableInts();
	SYS_setVIntCallback(&viewport_vint);
}

void viewport_refreshCurrentViewport() {
	Viewport_DATA->pausa = FALSE;
	s16 min = Viewport_DATA->currentPositionInTiles.pos1.x;
	s16 max = Viewport_DATA->currentPositionInTiles.pos2.x;
	for (s16 i = min; i <= max; ++i) {
		viewport_refreshColumn(i);
	}
}

void viewport_titleScreen() {
	Viewport_DATA->pausa = TRUE;
	for (s16 y = 0; y < 64; ++y) {
		for (s16 x = 0; x < 64; ++x) {
			VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL2, TRUE, 0, 0, (x < 60) ? 2 : 1), x, y);
		}
	}
}

void viewport_pause() {
	Viewport_DATA->pausa = TRUE;
	VDP_drawImageEx(PLAN_WINDOW, &pausa_screen, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, G_TILEINDEX_PAUSASCREEN), 0, 0, FALSE, FALSE);

}

void viewport_updateTitleScreen(u16 timer) {
	for (u8 i=0; i<VIEWPORT_HSCROLL_LINES_SIZE; ++i) {
		if (timer < 190) {
			Viewport_DATA->hzScrollLinesPlanA[i] = sinFix16((timer/3 + i)*40) / 15;
		} else {
			s16 ponderacion = timer - 190;
			Viewport_DATA->hzScrollLinesPlanA[i] = (sinFix16((timer/3 + i + ponderacion) * 40) * math_pow(2, timer - 180)) / 15;
		}
	}
	if (timer < 7) {
		s16 limitLeft = timer*2;
		u16 tileId;
		for (s16 y = 0; y < 64; ++y) {
			for (s16 x = 0; x <= limitLeft; ++x) {
				if (x < limitLeft) {
					tileId = 1;
				} else {
					tileId = 0x131;
				}
				VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL2, TRUE, 0, 0, tileId), x, y);
			}
		}
	}
	VDP_setHorizontalScrollLine(PLAN_A, 0, Viewport_DATA->hzScrollLinesPlanA, VIEWPORT_HSCROLL_LINES_SIZE, FALSE);
	VDP_setVerticalScroll(PLAN_A, Viewport_DATA->planAPosition.y);
}

void viewport_finalize() {
	MEM_free(Viewport_DATA);
	Viewport_DATA = 0;
}

void viewport_moveX(s16 x) {
	Viewport_DATA->rawPosition.x += limits_s16(x, VIEWPORT_MAX_LEFT_SPEED, VIEWPORT_MAX_RIGHT_SPEED);
	Viewport_DATA->rawPosition.x = limits_s16(Viewport_DATA->rawPosition.x, Viewport_DATA->limits.pos2.x, Viewport_DATA->limits.pos1.x);

	viewport_calculatePlanAXPosition();
	viewport_calculatePlanBXPosition();
	viewport_calculateCurrentXPosition();
	viewport_drawXTiles();
	viewport_updateLastXPosition();
}

void viewport_moveY(s16 y) {
	Viewport_DATA->rawPosition.y += limits_s16(y, VIEWPORT_MAX_UP_SPEED, VIEWPORT_MAX_DOWN_SPEED);
	Viewport_DATA->rawPosition.y = limits_s16(Viewport_DATA->rawPosition.y, Viewport_DATA->limits.pos1.y, Viewport_DATA->limits.pos2.y);

	viewport_calculatePlanAYPosition();
	viewport_calculatePlanBYPosition();
	viewport_calculateCurrentYPosition();
	viewport_drawYTiles();
	viewport_updateLastYPosition();
}

void viewport_planeARefresh() {
	s16 *arr = Viewport_DATA->hzScrollLinesPlanA;
	for (u8 line = 0; line < VIEWPORT_HSCROLL_LINES_SIZE; ++line) {
		arr[line] = Viewport_DATA->planAPosition.x;
	}
}

void viewport_planeBRefresh() {
	Viewport_DATA->callback3dfxPtr();
}

s16 viewport_getCurrentX() {
	return Viewport_DATA->rawPosition.x;
}

s16 viewport_getCurrentY() {
	return Viewport_DATA->rawPosition.y;
}

void viewport_refreshColumn(s16 x) {
	SYS_disableInts();
	s16 min = Viewport_DATA->currentPositionInTiles.pos1.y;
	s16 max = Viewport_DATA->currentPositionInTiles.pos2.y;
	for (s16 y = min; y <= max; ++y) {
		viewport_putPlanATile(x, y);
		viewport_putSprite(x, y);
	}
	SYS_enableInts();
}

void viewport_refreshRow(s16 y) {
	SYS_disableInts();
	s16 min = Viewport_DATA->currentPositionInTiles.pos1.x;
	s16 max = Viewport_DATA->currentPositionInTiles.pos2.x;
	for (s16 x = min; x <= max; ++x) {
		viewport_putPlanATile(x, y);
		viewport_putSprite(x, y);
	}
	SYS_enableInts();
}

void viewport_putPlanATile(s16 x, s16 y) {
	u8 tileId = map_getPlanA(x, y);
	u8 onTop = map_getOnTop(tileId);
	tiles_putMapTile(tileId, x, y, onTop);
}

void viewport_putSprite(s16 x, s16 y) {
	const u8 spriteId = map_getSprite(x, y);
	if (spriteId != 0) {
		Viewport_DATA->onSpriteReplaceCallback(spriteId, (x+1) * 160, (y+1) * 160);
	}
}

u8 viewport_isMovingUp() {
	return Viewport_DATA->currentPositionInTiles.pos1.y < Viewport_DATA->lastPositionInTiles.pos1.y;
}

u8 viewport_isMovingDown() {
	return Viewport_DATA->currentPositionInTiles.pos2.y > Viewport_DATA->lastPositionInTiles.pos2.y;
}

u8 viewport_isMovingLeft() {
	return Viewport_DATA->currentPositionInTiles.pos1.x < Viewport_DATA->lastPositionInTiles.pos1.x;
}

u8 viewport_isMovingRight() {
	return Viewport_DATA->currentPositionInTiles.pos2.x > Viewport_DATA->lastPositionInTiles.pos2.x;
}

void viewport_calculatePlanAXPosition() {
	Viewport_DATA->planAPosition.x = Viewport_DATA->rawPosition.x / 10;
}

void viewport_calculatePlanAYPosition() {
	Viewport_DATA->planAPosition.y = Viewport_DATA->rawPosition.y / 10;
}

void viewport_calculatePlanBXPosition() {
	Viewport_DATA->planBPosition.x = Viewport_DATA->rawPosition.x / 200;
}

void viewport_calculatePlanBYPosition() {
	Viewport_DATA->planBPosition.y = Viewport_DATA->rawPosition.y / 560;
}

void viewport_calculateCurrentXPosition() {
	Viewport_DATA->currentPositionInTiles.pos1.x = -((Viewport_DATA->planAPosition.x + VIEWPORT_TILEWIDTH) / VIEWPORT_TILEWIDTH);
	Viewport_DATA->currentPositionInTiles.pos2.x = -((Viewport_DATA->planAPosition.x - VIEWPORT_WIDTH)     / VIEWPORT_TILEWIDTH);
}

void viewport_calculateCurrentYPosition() {
	Viewport_DATA->currentPositionInTiles.pos1.y = (Viewport_DATA->planAPosition.y - VIEWPORT_TILEHEIGHT) / VIEWPORT_TILEHEIGHT;
	Viewport_DATA->currentPositionInTiles.pos2.y = (Viewport_DATA->planAPosition.y + VIEWPORT_HEIGHT)     / VIEWPORT_TILEHEIGHT;
}

void viewport_drawXTiles() {
	if (Viewport_DATA->pausa) {
		return;
	}
	if (viewport_isMovingLeft()) {
		viewport_refreshColumn(Viewport_DATA->currentPositionInTiles.pos1.x);
	}
	if (viewport_isMovingRight()) {
		viewport_refreshColumn(Viewport_DATA->currentPositionInTiles.pos2.x);
	}
}

void viewport_drawYTiles() {
	if (Viewport_DATA->pausa) {
		return;
	}
	if (viewport_isMovingUp()) {
		viewport_refreshRow(Viewport_DATA->currentPositionInTiles.pos1.y);
	}
	if (viewport_isMovingDown()) {
		viewport_refreshRow(Viewport_DATA->currentPositionInTiles.pos2.y);
	}
}

void viewport_updateLastXPosition() {
	Viewport_DATA->lastPositionInTiles.pos1.x = Viewport_DATA->currentPositionInTiles.pos1.x;
	Viewport_DATA->lastPositionInTiles.pos2.x = Viewport_DATA->currentPositionInTiles.pos2.x;
}

void viewport_updateLastYPosition() {
	Viewport_DATA->lastPositionInTiles.pos1.y = Viewport_DATA->currentPositionInTiles.pos1.y;
	Viewport_DATA->lastPositionInTiles.pos2.y = Viewport_DATA->currentPositionInTiles.pos2.y;
}

void viewport_vint() {
	if (Viewport_DATA && !Viewport_DATA->pausa) {
		VDP_setHorizontalScrollLine(PLAN_A, 0, Viewport_DATA->hzScrollLinesPlanA, VIEWPORT_HSCROLL_LINES_SIZE, FALSE);
		VDP_setHorizontalScrollLine(PLAN_B, 0, Viewport_DATA->hzScrollLinesPlanB, VIEWPORT_HSCROLL_LINES_SIZE, FALSE);
		VDP_setVerticalScroll(PLAN_A, Viewport_DATA->planAPosition.y);
		VDP_setVerticalScroll(PLAN_B, Viewport_DATA->planBPosition.y);
	}
}

void viewport_ocean3dfx() {
	s16 planBX = Viewport_DATA->planBPosition.x;
	s16 limitLine = VIEWPORT_OCEAN_LINE - Viewport_DATA->planBPosition.y;
	u16 line = 0;
	s16 *arr = Viewport_DATA->hzScrollLinesPlanB;
	while (line < limitLine) {
		arr[line] = planBX;
		 ++line;
	}
	s16 displacedLine = 1;
	s16 x;
	while (line < VIEWPORT_HSCROLL_LINES_SIZE) {
		if ((displacedLine & 3) == 1) {
			x = (Viewport_DATA->planAPosition.x * displacedLine) / 80 + planBX;
		}
		arr[line] = x;
		++line;
		++displacedLine;
	}
}
