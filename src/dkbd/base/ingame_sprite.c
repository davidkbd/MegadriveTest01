#include "ingame_sprite.h"

#include "viewport.h"

#include "screens_global.h"

void ingameSprite_enable(IngameSprite *sprite);
void ingameSprite_disable(IngameSprite *sprite);
u8 ingameSprite_isInVieport(IngameSprite *sprite);
u8 ingameSprite_isOutOfViewport(IngameSprite *sprite);

void ingameSprite_moveTo(IngameSprite *sprite, s16 x, s16 y) {
	ingameSprite_moveX(sprite, x - sprite->position.x);
	ingameSprite_moveY(sprite, y - sprite->position.y);
}

void ingameSprite_moveX(IngameSprite *sprite, s16 x) {
	sprite->position.x += x;
}

void ingameSprite_moveY(IngameSprite *sprite, s16 y) {
	sprite->position.y += y;
}

u8 ingameSprite_isStatic(IngameSprite *sprite) {
	return sprite->type->isStatic == 0;
}

u8 ingameSprite_isEnabled(IngameSprite *sprite) {
	return sprite->sprite != 0;
}

u8 ingameSprite_isDisabled(IngameSprite *sprite) {
	return sprite->sprite == 0;
}

void ingameSprite_applyPosition(IngameSprite *sprite) {
	s16 x = (sprite->posInViewport.x - sprite->type->xCenter) / 10;
	s16 y = (sprite->posInViewport.y - sprite->type->size.y) / 10;
	SPR_setPosition(sprite->sprite, x, y);
}

s8 ingameSprite_compareXPosition(IngameSprite *sprite1, IngameSprite *sprite2) {
	s16 x1 = sprite1->position.x + sprite1->type->xCenter;
	s16 x2 = sprite2->position.x + sprite2->type->xCenter;
	if (x1 < x2) {
		return -1;
	}
	if (x1 > x2) {
		return 1;
	}
	return 0;
}

void ingameSprite_updatePosInViewport(IngameSprite *sprite) {
	sprite->posInViewport.x = sprite->position.x + viewport_getCurrentX();
	sprite->posInViewport.y = sprite->position.y - viewport_getCurrentY();
}

void ingameSprite_enableOrDisableByViewport(IngameSprite *sprite) {
	if (ingameSprite_isDisabled(sprite) && ingameSprite_isInVieport(sprite)) {
		ingameSprite_enable(sprite);
	} else if (ingameSprite_isEnabled(sprite) && ingameSprite_isOutOfViewport(sprite)) {
		ingameSprite_disable(sprite);
	}
}

Rect ingameSprite_calculeCollider(IngameSprite *sprite) {
	Rect r;
	r.pos1.x = sprite->type->collider.pos1.x + sprite->position.x;
	r.pos1.y = sprite->type->collider.pos1.y + sprite->position.y;
	r.pos2.x = sprite->type->collider.pos2.x + sprite->position.x;
	r.pos2.y = sprite->type->collider.pos2.y + sprite->position.y;
	return r;
}

Rect ingameSprite_calculateFootsCollider(IngameSprite *sprite) {
	Rect r;
	r.pos1.x = sprite->type->footsCollider.pos1.x + sprite->position.x;
	r.pos1.y = sprite->type->footsCollider.pos1.y + sprite->position.y;
	r.pos2.x = sprite->type->footsCollider.pos2.x + sprite->position.x;
	r.pos2.y = sprite->type->footsCollider.pos2.y + sprite->position.y;
	return r;
}

void ingameSprite_enable(IngameSprite *sprite) {
	u8 spriteId = sprite->spriteId;
	u16 tileIndex = G_TILEINDEX_SPRITES + spriteId * 12;
//	sprite->sprite = SPR_addSprite(sprite->type->spriteDef, 0, 0, TILE_ATTR_FULL(sprite->type->palette, TRUE, FALSE, FALSE, tileIndex));
	sprite->sprite = SPR_addSpriteEx(sprite->type->spriteDef, 0, 0, TILE_ATTR_FULL(sprite->type->palette, TRUE, FALSE, FALSE, tileIndex), spriteId, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	//SPR_setAlwaysOnTop(sprite->sprite, sprite->alwaysOnTop);
}

void ingameSprite_disable(IngameSprite *sprite) {
	SPR_releaseSprite(sprite->sprite);
	sprite->sprite = 0;
}
u8 ingameSprite_isInVieport(IngameSprite *sprite) {
	s16 minx = -viewport_getCurrentX() - sprite->type->size.x;
	s16 miny =  viewport_getCurrentY() - sprite->type->size.y;
	s16 maxx = -viewport_getCurrentX() + 3200 + sprite->type->size.x;
	s16 maxy =  viewport_getCurrentY() + 2240 + sprite->type->size.y;
	return
			sprite->position.x > minx &&
			sprite->position.x < maxx &&
			sprite->position.y > miny &&
			sprite->position.y < maxy;
}

u8 ingameSprite_isOutOfViewport(IngameSprite *sprite) {
	s16 minx = -viewport_getCurrentX() - sprite->type->size.x;
	s16 miny =  viewport_getCurrentY() - sprite->type->size.y;
	s16 maxx = -viewport_getCurrentX() + 3200 + sprite->type->size.x;
	s16 maxy =  viewport_getCurrentY() + 2240 + sprite->type->size.y;
	return
			sprite->position.x < minx ||
			sprite->position.x > maxx ||
			sprite->position.y < miny ||
			sprite->position.y > maxy;
}

