#include <genesis.h>

#include "testingame.h"
#include "testingame_private.h"
#include "testingame_private_ia.h"
#include "testingame_private_sceneanim.h"

#include "../base/event_timer_handler.h"
#include "../base/hud.h"
#include "../base/viewport.h"
#include "../util/map.h"

//#include "../../../res/sprite.h"
//#include "../../../res/gfx.h"

void testIngame_updateSprites();
void testIngame_updateSpritesPositionInViewport(TestIngame_Sprite *sprite);
void testIngame_updateOrDestroySprites(TestIngame_Sprite *sprite);
void testIngame_applySprites();
void testIngame_moveViewport();
void testIngame_applyMapRestrictions();
void testInGame_getColliderPositions(Rect *cell, Rect *posInCell);

void testIngame_update() {
	++TestIngame_DATA->screenData.frameCount;
	eventTimerHandler_update();
	hud_updateTimer();
	testIngame_updateControls();
	testIngame_updateSprites();
	testIngame_moveViewport();
	testIngame_applySprites();
	testIngame_updateSceneAnimation();
	hud_updateScore(getFPS());
}

void testIngame_initialize() {
	testIngame_initUI();
	testIngame_initMemory();
	testIngame_initData();
	testIngame_initSound();
	testIngame_initPalete();
	testIngame_initBackgrounds();
	testIngame_initSprites();
	testIngame_beginStart();
}

void testIngame_updateSprites() {
	for (u8 i = 0; i < TestIngame_NUM_SPRITES; ++i) {
		TestIngame_Sprite *s = &(TestIngame_DATA->sprites[i]);
		if (s->update) {
			s->update(s);
		}
	}
}

void testIngame_updateSpritesPositionInViewport(TestIngame_Sprite *sprite) {
	sprite->posInViewport.x = sprite->position.x + viewport_getCurrentX();
	sprite->posInViewport.y = sprite->position.y - viewport_getCurrentY();
}

void testIngame_updateOrDestroySprites(TestIngame_Sprite *sprite) {
	s16 minx = -viewport_getCurrentX() - sprite->size.x;
	s16 miny = viewport_getCurrentY() - sprite->size.y;
	s16 maxx = -viewport_getCurrentX() + 3200;
	s16 maxy = viewport_getCurrentY() + 2240;
	if (sprite->sprite == 0 && sprite->position.x > minx && sprite->position.x < maxx && sprite->position.y > miny && sprite->position.y < maxy) {
		sprite->sprite = SPR_addSprite(sprite->spriteDef, 0, 0, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
		SPR_setAlwaysOnTop(sprite->sprite, sprite->alwaysOnTop);
	} else if (sprite->sprite != 0 && (sprite->position.x < minx || sprite->position.x > maxx || sprite->position.y < miny || sprite->position.y > maxy)) {
		SPR_releaseSprite(sprite->sprite);
		sprite->sprite = 0;
	}
}

void testIngame_applySprites() {
	for (u8 i = 0; i < TestIngame_NUM_SPRITES; ++i) {
		TestIngame_Sprite *s = &(TestIngame_DATA->sprites[i]);
		testIngame_updateSpritesPositionInViewport(s);
		if (i != 0) {
			testIngame_updateOrDestroySprites(s);
		}
		if (s->sprite != 0) {
			s16 x = (s->posInViewport.x - s->xCenter) / 10;
			s16 y = (s->posInViewport.y - s->size.y)   / 10;
			SPR_setPosition(s->sprite, x, y);
		}
	}
}

void testIngame_moveViewport() {
	TestIngame_Sprite *s = TestIngame_DATA->playerSpritePTR;
	s16 moveX = (1600 - s->posInViewport.x) / 8;
	s16 moveY = (1200 - s->posInViewport.y) / 8;
	if (abs(moveX) > 2) {
		viewport_moveX(moveX);
	}
	if (abs(moveY) > 2) {
		viewport_moveY(-moveY);
	}
}

void testIngame_applyMapRestrictions() {
	Rect cell;
	Rect posInCell;
	testInGame_getColliderPositions(&cell, &posInCell);
	u16 restrictionUL = map_getRestriction(cell.pos1.x, cell.pos1.y);
	u16 restrictionUR = map_getRestriction(cell.pos2.x, cell.pos1.y);
	u16 restrictionDR = map_getRestriction(cell.pos2.x, cell.pos2.y);
	u16 restrictionDL = map_getRestriction(cell.pos1.x, cell.pos2.y);

	Vector2 *sprPos = &(TestIngame_DATA->playerSpritePTR->position);

	if (posInCell.pos2.x < 40 && ((0b00000010 & restrictionUR) || (0b00000010 & restrictionDR))) {
		TestIngame_DATA->playerData.xSpeed = 0;
		sprPos->x -= 2;
	}
	if (posInCell.pos1.x > 120 && ((0b00001000 & restrictionUL) || (0b00001000 & restrictionDL))) {
		TestIngame_DATA->playerData.xSpeed = 0;
		sprPos->x += 2;
	}
	if (posInCell.pos2.y < 40 && ((0b00000100 & restrictionDL) || (0b00000100 & restrictionDR))) {
		TestIngame_DATA->playerData.ySpeed = 0;
		sprPos->y -= 2;
	}
	if (posInCell.pos1.y > 120 && ((0b00000001 & restrictionUL) || (0b00000001 & restrictionUR))) {
		TestIngame_DATA->playerData.ySpeed = 0;
		sprPos->y += 2;
	}
}

void testInGame_getColliderPositions(Rect *cell, Rect *posInCell) {
	Vector2 pos1 = vector2_add(
			&(TestIngame_DATA->playerSpritePTR->collider.pos1),
			&(TestIngame_DATA->playerSpritePTR->position));
	Vector2 pos2 = vector2_add(
			&(TestIngame_DATA->playerSpritePTR->collider.pos2),
			&(TestIngame_DATA->playerSpritePTR->position));

	cell->pos1.x = pos1.x / 160;
	cell->pos1.y = pos1.y / 160;
	cell->pos2.x = pos2.x / 160;
	cell->pos2.y = pos2.y / 160;
	posInCell->pos1.x = pos1.x % 160;
	posInCell->pos1.y = pos1.y % 160;
	posInCell->pos2.x = pos2.x % 160;
	posInCell->pos2.y = pos2.y % 160;
}

void testIngame_onPlayerUpdate(TestIngame_Sprite *sprite) {
	if (TestIngame_DATA->playerData.xSpeed != 0 || TestIngame_DATA->playerData.ySpeed != 0) {
		testIngame_applyMapRestrictions();
		sprite->position.x += TestIngame_DATA->playerData.xSpeed;
		sprite->position.y += TestIngame_DATA->playerData.ySpeed;
	}
	if (testIngame_isPressingUp()) {
		if (testIngame_isPressingLeft()) {
			SPR_setAnim(sprite->sprite, 8);
		} else if (testIngame_isPressingRight()) {
			SPR_setAnim(sprite->sprite, 2);
		} else {
			SPR_setAnim(sprite->sprite, 1);
		}
	} else if (testIngame_isPressingDown()) {
		if (testIngame_isPressingLeft()) {
			SPR_setAnim(sprite->sprite, 6);
		} else if (testIngame_isPressingRight()) {
			SPR_setAnim(sprite->sprite, 4);
		} else {
			SPR_setAnim(sprite->sprite, 5);
		}
	} else {
		if (testIngame_isPressingLeft()) {
			SPR_setAnim(sprite->sprite, 7);
		} else if (testIngame_isPressingRight()) {
			SPR_setAnim(sprite->sprite, 3);
		} else {
			SPR_setAnim(sprite->sprite, 0);
		}
	}
}
