#include <genesis.h>

#include "ingame_platforms.h"
#include "ingame_platforms_private.h"
#include "ingame_platforms_private_ia.h"
#include "ingame_platforms_private_sceneanim.h"

#include "../base/event_timer_handler.h"
#include "../base/hud.h"
#include "../base/viewport.h"
#include "../util/map.h"
#include "../util/limits.h"

//#include "../../../res/sprite.h"
//#include "../../../res/gfx.h"

void ingamePlatforms_updateSprites();
void ingamePlatforms_updateSpritesPositionInViewport(IngamePlatforms_Sprite *sprite);
void ingamePlatforms_updateOrDestroySprites(IngamePlatforms_Sprite *sprite);
void ingamePlatforms_applySprites();
void ingamePlatforms_moveViewport();
void ingamePlatforms_applyMapRestrictions();
void ingamePlatforms_getColliderPositions(Rect *cell, Rect *posInCell);

void ingamePlatforms_update() {
	++IngamePlatforms_DATA->screenData.frameCount;
	eventTimerHandler_update();
	hud_updateTimer();
	ingamePlatforms_updateControls();
	ingamePlatforms_updateSprites();
	ingamePlatforms_moveViewport();
	ingamePlatforms_applySprites();
	ingamePlatforms_updateSceneAnimation();
	hud_updateScore(getFPS());
}

void ingamePlatforms_initialize() {
	ingamePlatforms_initUI();
	ingamePlatforms_initMemory();
	ingamePlatforms_initData();
	ingamePlatforms_initSound();
	ingamePlatforms_initPalete();
	ingamePlatforms_initBackgrounds();
	ingamePlatforms_initSprites();
	ingamePlatforms_beginStart();
}

void ingamePlatforms_updateSprites() {
	for (u8 i = 0; i < IngamePlatforms_NUM_SPRITES; ++i) {
		IngamePlatforms_Sprite *s = &(IngamePlatforms_DATA->sprites[i]);
		if (s->update) {
			s->update(s);
		}
	}
}

void ingamePlatforms_updateSpritesPositionInViewport(IngamePlatforms_Sprite *sprite) {
	sprite->posInViewport.x = sprite->position.x + viewport_getCurrentX();
	sprite->posInViewport.y = sprite->position.y - viewport_getCurrentY();
}

void ingamePlatforms_updateOrDestroySprites(IngamePlatforms_Sprite *sprite) {
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

void ingamePlatforms_applySprites() {
	for (u8 i = 0; i < IngamePlatforms_NUM_SPRITES; ++i) {
		IngamePlatforms_Sprite *s = &(IngamePlatforms_DATA->sprites[i]);
		ingamePlatforms_updateSpritesPositionInViewport(s);
		if (i != 0) {
			ingamePlatforms_updateOrDestroySprites(s);
		}
		if (s->sprite != 0) {
			s16 x = (s->posInViewport.x - s->xCenter) / 10;
			s16 y = (s->posInViewport.y - s->size.y)   / 10;
			SPR_setPosition(s->sprite, x, y);
		}
	}
}

void ingamePlatforms_moveViewport() {
	IngamePlatforms_Sprite *s = IngamePlatforms_DATA->playerSpritePTR;
	s16 moveX = (1600 - s->posInViewport.x) / 8;
	s16 moveY = (1200 - s->posInViewport.y) / 8;
	if (abs(moveX) > 2) {
		viewport_moveX(moveX);
	}
	if (abs(moveY) > 2) {
		viewport_moveY(-moveY);
	}
}

void ingamePlatforms_applyMapRestrictions() {
	Rect cell;
	Rect posInCell;
	ingamePlatforms_getColliderPositions(&cell, &posInCell);
	u16 restrictionUL = map_getRestriction(cell.pos1.x, cell.pos1.y);
	u16 restrictionUR = map_getRestriction(cell.pos2.x, cell.pos1.y);
	u16 restrictionDR = map_getRestriction(cell.pos2.x, cell.pos2.y);
	u16 restrictionDL = map_getRestriction(cell.pos1.x, cell.pos2.y);
	Vector2 *speed = &IngamePlatforms_DATA->playerSpritePTR->speed;
	Vector2 *sprPos = &IngamePlatforms_DATA->playerSpritePTR->position;

	if ((0b00000010 & restrictionUR)) {
		if (speed->x > 0) {
			speed->x = 0;
		}
		if (posInCell.pos2.x < 80 && posInCell.pos2.x >= 0) {
			sprPos->x -= 1;
		}
	}
	if ((0b00001000 & restrictionUL)) {
		if (speed->x < 0) {
			speed->x = 0;
		}
		if (posInCell.pos1.x > 79 && posInCell.pos1.x < 160) {
			sprPos->x += 1;
		}
	}
	if (!((0b00000100 & restrictionDL) || (0b00000100 & restrictionDR))) {
		IngamePlatforms_DATA->playerSpritePTR->onFloor = 0;
	} else if ((0b00000100 & restrictionDL) || (0b00000100 & restrictionDR)) {
		if (speed->y > 0) {
			IngamePlatforms_DATA->playerSpritePTR->onFloor = 1;
			speed->y = 0;
		}
		if (posInCell.pos2.y < 160) {
			sprPos->y -= 1;
		}
	}
	if ((0b00000001 & restrictionUL) || (0b00000001 & restrictionUR)) {
		if (speed->y < 0) {
			speed->y = 0;
		}
//		if (posInCell.pos1.y < 80 && posInCell.pos1.y >= 0) {
			sprPos->y += 1;
//		}
	}

}

void ingamePlatforms_getColliderPositions(Rect *cell, Rect *posInCell) {
	Vector2 pos1 = vector2_add(
			&(IngamePlatforms_DATA->playerSpritePTR->collider.pos1),
			&(IngamePlatforms_DATA->playerSpritePTR->position));
	Vector2 pos2 = vector2_add(
			&(IngamePlatforms_DATA->playerSpritePTR->collider.pos2),
			&(IngamePlatforms_DATA->playerSpritePTR->position));

	cell->pos1.x = pos1.x / 160;
	cell->pos1.y = pos1.y / 160;
	cell->pos2.x = pos2.x / 160;
	cell->pos2.y = pos2.y / 160;
	posInCell->pos1.x = pos1.x % 160;
	posInCell->pos1.y = pos1.y % 160;
	posInCell->pos2.x = pos2.x % 160;
	posInCell->pos2.y = pos2.y % 160;
}

void ingamePlatforms_onPlayerUpdate(IngamePlatforms_Sprite *sprite) {
	Vector2 *speed = &IngamePlatforms_DATA->playerSpritePTR->speed;
	if (!IngamePlatforms_DATA->playerSpritePTR->onFloor) {
		speed->y = limits_incr_s16(
				speed->y,
				IngamePlatforms_DATA->gravity,
				-80,
				60);
	}

	if (speed->x != 0 || speed->y != 0) {
		ingamePlatforms_applyMapRestrictions();
		sprite->position.x += speed->x;
		sprite->position.y += speed->y;
	}

	if (ingamePlatforms_isPressingUp()) {
		if (ingamePlatforms_isPressingLeft()) {
			SPR_setAnim(sprite->sprite, 8);
		} else if (ingamePlatforms_isPressingRight()) {
			SPR_setAnim(sprite->sprite, 2);
		} else {
			SPR_setAnim(sprite->sprite, 1);
		}
	} else if (ingamePlatforms_isPressingDown()) {
		if (ingamePlatforms_isPressingLeft()) {
			SPR_setAnim(sprite->sprite, 6);
		} else if (ingamePlatforms_isPressingRight()) {
			SPR_setAnim(sprite->sprite, 4);
		} else {
			SPR_setAnim(sprite->sprite, 5);
		}
	} else {
		if (ingamePlatforms_isPressingLeft()) {
			SPR_setAnim(sprite->sprite, 7);
		} else if (ingamePlatforms_isPressingRight()) {
			SPR_setAnim(sprite->sprite, 3);
		} else {
			SPR_setAnim(sprite->sprite, 0);
		}
	}
}


