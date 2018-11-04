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
void ingamePlatforms_applySprites();
void ingamePlatforms_applySprite(IngameSprite *s);
void ingamePlatforms_moveViewport(IngameSprite *sprite);
void ingamePlatforms_applyMapRestrictions(IngameSprite *sprite);
void ingamePlatforms_applyHorizontalMapRestrictions(IngameSprite *sprite, Rect *posInCell, u16 restrictionUR, u16 restrictionDR, u16 restrictionUL, u16 restrictionDL);
void ingamePlatforms_applyFootRestrictions(IngameSprite *sprite, Rect *posInCell, u16 restrictionFoots, u16 restrictionDR, u16 restrictionDL);
void ingamePlatforms_applyHeadRestrictions(IngameSprite *sprite, u16 restrictionUL, u16 restrictionUR);
s16 ingamePlatforms_calculateFootRelaxPosition(u16 restriction, s16 spriteXInCell);
void ingamePlatforms_putOnFloor(Vector2 *posInCell, IngameSprite *sprite, s16 yRelaxPosition);
void ingamePlatforms_applyGravity(IngameSprite *sprite);
void ingamePlatforms_getColliderPositions(Rect *collider, Vector2 *posTop, Vector2 *posBottom, Rect *posInCell);

void ingamePlatforms_update() {
	IngamePlatforms_DATA->ingame_updatePtr();
}

void ingamePlatforms_update_titleScreen() {
	eventTimerHandler_update();
}

void ingamePlatforms_update_ingame() {
	++IngamePlatforms_DATA->screenData.frameCount;
	eventTimerHandler_update();
	ingamePlatforms_updateControls();
	ingamePlatforms_updateSprites();
	ingamePlatforms_moveViewport(IngamePlatforms_DATA->playerSpritePTR);
	ingamePlatforms_applySprites();
	ingamePlatforms_updateSceneAnimation();
	//hud_updateScore(IngamePlatforms_DATA->playerSpritePTR->position.x/80);
screensGlobal_setScore(IngamePlatforms_DATA->screenData.frameCount);
//screensGlobal_setLifes(getFPS());
	viewport_planeARefresh();
	viewport_planeBRefresh();
	hud_updateTimer();
	hud_updateLifes();
	hud_updateScore();
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
		IngameSprite *s = &(IngamePlatforms_DATA->sprites[i]);
		if (ingameSprite_isEnabled(s)) {
			s->update(s);
		}
	}
}

void ingamePlatforms_applySprites() {
	ingameSprite_updatePosInViewport(IngamePlatforms_DATA->playerSpritePTR);
	ingamePlatforms_applyGravity(IngamePlatforms_DATA->playerSpritePTR);
	ingamePlatforms_applyMapRestrictions(IngamePlatforms_DATA->playerSpritePTR);
	ingameSprite_applyPosition(IngamePlatforms_DATA->playerSpritePTR);
	for (u8 i = 1; i < IngamePlatforms_NUM_SPRITES; ++i) {
		ingamePlatforms_applySprite(&(IngamePlatforms_DATA->sprites[i]));
	}
}

void ingamePlatforms_applySprite(IngameSprite *s) {
	ingameSprite_updatePosInViewport(s);
	ingameSprite_enableOrDisableByViewport(s);
	if (ingameSprite_isEnabled(s)) {
		if (!ingameSprite_isStatic(s)) {
			ingamePlatforms_applyGravity(s);
			ingamePlatforms_applyMapRestrictions(s);
		}
		ingameSprite_applyPosition(s);
	}
}

void ingamePlatforms_moveViewport(IngameSprite *sprite) {
	s16 moveX = (IngamePlatforms_DATA->screenData.viewportOffset.x - sprite->posInViewport.x) / 8;
	s16 moveY = (IngamePlatforms_DATA->screenData.viewportOffset.y - sprite->posInViewport.y) / 8;
	if (abs(moveX) > 2 || abs(moveY) > 2) {
		viewport_moveY(-moveY);
		viewport_moveX(moveX);
	}
}

void ingamePlatforms_applyMapRestrictions(IngameSprite *sprite) {
	Vector2 posTopLeft;
	Vector2 posBottomRight;
	Rect posInCell;
	s16 midY = (sprite->position.y - sprite->type->yCenter) / 160;
	Rect spriteCollider = ingameSprite_calculateCollider(sprite);
	ingamePlatforms_getColliderPositions(&spriteCollider, &posTopLeft, &posBottomRight, &posInCell);
	u16 restrictionUL    = map_getRestriction(posTopLeft.x, posTopLeft.y);
	u16 restrictionUR    = map_getRestriction(posBottomRight.x, posTopLeft.y);
	u16 restrictionML    = map_getRestriction(posTopLeft.x, midY);
	u16 restrictionMR    = map_getRestriction(posBottomRight.x, midY);
	u16 restrictionDR    = map_getRestriction(posBottomRight.x, posBottomRight.y);
	u16 restrictionDL    = map_getRestriction(posTopLeft.x, posBottomRight.y);
	u16 restrictionFoots = map_getRestriction(sprite->position.x / 160, posBottomRight.y);

	ingamePlatforms_applyHorizontalMapRestrictions(sprite, &posInCell, restrictionMR, restrictionDR, restrictionML, restrictionDL);
	ingamePlatforms_applyFootRestrictions(sprite, &posInCell, restrictionFoots, restrictionDR, restrictionDL);
	ingamePlatforms_applyHeadRestrictions(sprite, restrictionUL, restrictionUR);
}

void ingamePlatforms_applyHorizontalMapRestrictions(IngameSprite *sprite, Rect *posInCell, u16 restrictionUR, u16 restrictionDR, u16 restrictionUL, u16 restrictionDL) {
	if (((MAP_RESTRICTION_RIGHT & restrictionUR)) && !(sprite->onFloor && (0b00000110 & restrictionDR))) {
		if (sprite->speed.x > 0) {
			sprite->speed.x = 0;
		}
		while (posInCell->pos2.x > 10) {
			ingameSprite_moveX(sprite, -1);
			--posInCell->pos1.x;
			--posInCell->pos2.x;
		}
		sprite->pushing = 1;
	} else if (((MAP_RESTRICTION_LEFT & restrictionUL)) && !(sprite->onFloor && (0b00001100 & restrictionDL))) {
		if (sprite->speed.x < 0) {
			sprite->speed.x = 0;
		}
		while (posInCell->pos1.x < 159) {
			ingameSprite_moveX(sprite, 1);
			++posInCell->pos1.x;
			++posInCell->pos2.x;
		}
		sprite->pushing = -1;
	} else {
		sprite->pushing = 0;
	}
}

void ingamePlatforms_applyFootRestrictions(IngameSprite *sprite, Rect *posInCell, u16 restrictionFoots, u16 restrictionDR, u16 restrictionDL) {
	if (MAP_RESTRICTION_DOWN & restrictionFoots) {
		s16 spriteXInCell = sprite->position.x % 160;
		s16 yRelaxPosition = ingamePlatforms_calculateFootRelaxPosition(restrictionFoots, spriteXInCell);
		if (sprite->speed.y > 0) {
			if (posInCell->pos2.y >= yRelaxPosition) {
				sprite->onFloor = 1;
				sprite->speed.y = 0;
			}
			if ((MAP_RESTRICTION_ISRAMP & restrictionFoots)) {
				sprite->speed.y = 20;
			}
			ingamePlatforms_putOnFloor(&(posInCell->pos2), sprite, yRelaxPosition);
		}
		if (!(MAP_RESTRICTION_ISRAMP & restrictionFoots) && restrictionDL == 0 && posInCell->pos1.x < 110) {
			sprite->onPlatformBorder = -1;
		} else if (!(MAP_RESTRICTION_ISRAMP & restrictionFoots) && restrictionDR == 0 && posInCell->pos2.x > 60) {
			sprite->onPlatformBorder = 1;
		} else {
			sprite->onPlatformBorder = 0;
		}
	} else {
		sprite->onFloor = 0;
	}
}

void ingamePlatforms_applyHeadRestrictions(IngameSprite *sprite, u16 restrictionUL, u16 restrictionUR) {
	if ((MAP_RESTRICTION_UP & restrictionUL) || (MAP_RESTRICTION_UP & restrictionUR)) {
		if (sprite->speed.y < 0) {
			sprite->speed.y = 0;
		}
		ingameSprite_moveY(sprite, 1);
	}
}

s16 ingamePlatforms_calculateFootRelaxPosition(u16 restriction, s16 spriteXInCell) {
	s16 yRelaxPosition;
	if (MAP_RESTRICTION_ISRAMP & restriction) {
		if (MAP_RESTRICTION_ISRAMPLEFT & restriction) {
			if (MAP_RESTRICTION_ISRAMPHARD & restriction) {
				yRelaxPosition = 160-spriteXInCell;
			} else {
				yRelaxPosition = 80-spriteXInCell / 2;
			}
		} else {
			if (MAP_RESTRICTION_ISRAMPHARD & restriction) {
				yRelaxPosition = spriteXInCell;
			} else {
				yRelaxPosition = spriteXInCell / 2;
			}
		}
	} else {
		yRelaxPosition = 0;
	}
	if (MAP_RESTRICTION_ISBOTTOMTILE & restriction) {
		yRelaxPosition -= 160;
	}
	if (MAP_RESTRICTION_ISDISPLACED & restriction) {
		yRelaxPosition += 80;
	}
	yRelaxPosition += 10;
	return yRelaxPosition;
}

void ingamePlatforms_putOnFloor(Vector2 *posInCell, IngameSprite *sprite, s16 yRelaxPosition) {
	while (posInCell->y < yRelaxPosition) {
		ingameSprite_moveY(sprite, 1);
		++posInCell->y;
	}
	while (posInCell->y > yRelaxPosition) {
		ingameSprite_moveY(sprite, -1);
		--posInCell->y;
	}
}

void ingamePlatforms_applyGravity(IngameSprite *sprite) {
	sprite->speed.y = limits_incr_s16(
			sprite->speed.y,
			IngamePlatforms_DATA->gravity,
			INGAME_PLATFORMS_MAX_JUMP_SPEED,
			INGAME_PLATFORMS_MAX_FALLING_SPEED);
}

void ingamePlatforms_getColliderPositions(Rect *collider, Vector2 *posTopLeft, Vector2 *posBottomRight, Rect *posInCell) {
	posTopLeft->x = collider->pos1.x / 160;
	posTopLeft->y = collider->pos1.y / 160;
	posBottomRight->x = collider->pos2.x / 160;
	posBottomRight->y = collider->pos2.y / 160;
	posInCell->pos1.x = collider->pos1.x % 160;
	posInCell->pos1.y = collider->pos1.y % 160;
	posInCell->pos2.x = collider->pos2.x % 160;
	posInCell->pos2.y = collider->pos2.y % 160;
}

void ingamePlatforms_onViewportSprite(u8 spriteId, s16 x, s16 y) {
	ingameSprite_moveTo(&(IngamePlatforms_DATA->sprites[spriteId]), x, y);
}

void ingamePlatforms_onPlayerUpdate(IngameSprite *sprite) {
	ingameSprite_moveX(sprite, sprite->speed.x);
	ingameSprite_moveY(sprite, sprite->speed.y);

	if (ingamePlatforms_isPressingRight()) {
		SPR_setHFlip(sprite->sprite, FALSE);
	} else if (ingamePlatforms_isPressingLeft()) {
		SPR_setHFlip(sprite->sprite, TRUE);
	}
	if (ingamePlatforms_isPressingAction()) {
		SPR_setAnim(sprite->sprite, 4);
	} else if (!sprite->onFloor) {
		SPR_setAnim(sprite->sprite, 2);
	} else if (sprite->pushing != 0) {
		SPR_setHFlip(sprite->sprite, (sprite->pushing < 0));
		SPR_setAnim(sprite->sprite, 6);
	} else if (ingamePlatforms_isPressingRight()) {
		SPR_setAnim(sprite->sprite, 1);
	} else if (ingamePlatforms_isPressingLeft()) {
		SPR_setAnim(sprite->sprite, 1);
	} else if (sprite->onPlatformBorder != 0) {
		SPR_setHFlip(sprite->sprite, (sprite->onPlatformBorder < 0));
		SPR_setAnim(sprite->sprite, 5);
	} else {
		SPR_setAnim(sprite->sprite, 0);
	}
}

