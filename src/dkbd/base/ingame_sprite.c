#include "ingame_sprite.h"

#include "viewport.h"

void ingameSprite_moveTo(IngameSprite *sprite, s16 x, s16 y) {
	ingameSprite_moveX(sprite, x - sprite->position.x);
	ingameSprite_moveY(sprite, y - sprite->position.y);
}

void ingameSprite_moveX(IngameSprite *sprite, s16 x) {
	sprite->position.x += x;
	sprite->collider.pos1.x += x;
	sprite->collider.pos2.x += x;
	sprite->footsCollider.pos1.x += x;
	sprite->footsCollider.pos2.x += x;
}

void ingameSprite_moveY(IngameSprite *sprite, s16 y) {
	sprite->position.y += y;
	sprite->collider.pos1.y += y;
	sprite->collider.pos2.y += y;
	sprite->footsCollider.pos1.y += y;
	sprite->footsCollider.pos2.y += y;
}

u8 ingameSprite_isEnabled(IngameSprite *sprite) {
	return sprite->sprite != 0;
}

u8 ingameSprite_isDisabled(IngameSprite *sprite) {
	return sprite->sprite == 0;
}

void ingameSprite_enable(IngameSprite *sprite) {
	sprite->sprite = SPR_addSprite(sprite->spriteDef, 0, 0, TILE_ATTR(sprite->palette, TRUE, FALSE, FALSE));
	SPR_setAlwaysOnTop(sprite->sprite, sprite->alwaysOnTop);
}

void ingameSprite_disable(IngameSprite *sprite) {
	SPR_releaseSprite(sprite->sprite);
	sprite->sprite = 0;
}

u8 ingameSprite_isInVieport(IngameSprite *sprite) {
	s16 minx = -viewport_getCurrentX() - sprite->size.x;
	s16 miny =  viewport_getCurrentY() - sprite->size.y;
	s16 maxx = -viewport_getCurrentX() + 3200 + sprite->size.x;
	s16 maxy =  viewport_getCurrentY() + 2240 + sprite->size.y;
	return
			sprite->position.x > minx &&
			sprite->position.x < maxx &&
			sprite->position.y > miny &&
			sprite->position.y < maxy;
}

u8 ingameSprite_isOutOfViewport(IngameSprite *sprite) {
	s16 minx = -viewport_getCurrentX() - sprite->size.x;
	s16 miny =  viewport_getCurrentY() - sprite->size.y;
	s16 maxx = -viewport_getCurrentX() + 3200 + sprite->size.x;
	s16 maxy =  viewport_getCurrentY() + 2240 + sprite->size.y;
	return
			sprite->position.x < minx ||
			sprite->position.x > maxx ||
			sprite->position.y < miny ||
			sprite->position.y > maxy;
}

void ingameSprite_applyPosition(IngameSprite *sprite) {
	s16 x = (sprite->posInViewport.x - sprite->xCenter) / 10;
	s16 y = (sprite->posInViewport.y - sprite->size.y)  / 10;
	SPR_setPosition(sprite->sprite, x, y);
}

s8 ingameSprite_comparePosition(IngameSprite *sprite1, IngameSprite *sprite2) {
	s16 x1 = sprite1->position.x + sprite1->xCenter;
	s16 x2 = sprite2->position.x + sprite2->xCenter;
	if (x1 < x2) {
		return -1;
	}
	if (x1 > x2) {
		return 1;
	}
	return 0;
}
