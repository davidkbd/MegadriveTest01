#include <genesis.h>

#include "../util/vector2.h"
#include "../util/rect.h"

#ifndef INGAMESPRITE_H_
#define INGAMESPRITE_H_

struct IngameSprite_st {
	const SpriteDefinition *spriteDef;
	u8 palette;
	u8 alwaysOnTop;
	Sprite* sprite;
	Vector2 position;
	Vector2 posInViewport;
	Vector2 speed;
	Vector2 size; // Visualmente, utilizado para saber si cargar o destruir al hacer scroll
	u8 onFloor;
	s8 onPlatformBorder;
	s8 pushing;
	u8 xCenter;
	u8 yCenter;
	Rect collider;
	Rect footsCollider;
	//0xFFFF
	u16 data;
	//Callback de actualizacion
	void (*update)(struct IngameSprite_st *sprite);
};
typedef struct IngameSprite_st IngameSprite;
#endif


void ingameSprite_moveTo(IngameSprite *sprite, s16 x, s16 y);
void ingameSprite_moveX(IngameSprite *sprite, s16 x);
void ingameSprite_moveY(IngameSprite *sprite, s16 y);
u8 ingameSprite_isEnabled(IngameSprite *sprite);
u8 ingameSprite_isDisabled(IngameSprite *sprite);
void ingameSprite_enable(IngameSprite *sprite);
void ingameSprite_disable(IngameSprite *sprite);
u8 ingameSprite_isInVieport(IngameSprite *sprite);
u8 ingameSprite_isOutOfViewport(IngameSprite *sprite);
void ingameSprite_applyPosition(IngameSprite *sprite);
s8 ingameSprite_comparePosition(IngameSprite *sprite1, IngameSprite *sprite2);

