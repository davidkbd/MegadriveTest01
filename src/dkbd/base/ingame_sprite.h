#include <genesis.h>

#include "ingame_sprite_type.h"

#include "../util/vector2.h"
#include "../util/rect.h"

#ifndef INGAMESPRITE_H_
#define INGAMESPRITE_H_

struct IngameSprite_st {
	u8 spriteId;
	const IngameSprite_Type *type;
	// Instancia del sprite
	Sprite* sprite;
	// Posicion absoluta
	Vector2 position;
	// Posicion respecto al viewport
	Vector2 posInViewport;
	// Velocidad de movimiento
	Vector2 speed;
	// Tocando suelo
	u8 onFloor;
	// Al borde de una plataforma
	s8 onPlatformBorder;
	// Empujando
	s8 pushing;
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
u8   ingameSprite_isStatic(IngameSprite *sprite);
u8   ingameSprite_isEnabled(IngameSprite *sprite);
u8   ingameSprite_isDisabled(IngameSprite *sprite);
void ingameSprite_applyPosition(IngameSprite *sprite);
s8   ingameSprite_compareXPosition(IngameSprite *sprite1, IngameSprite *sprite2);
void ingameSprite_updatePosInViewport(IngameSprite *sprite);
void ingameSprite_enableOrDisableByViewport(IngameSprite *sprite);
Rect ingameSprite_calculateCollider(IngameSprite *sprite);
Rect ingameSprite_calculateFootsCollider(IngameSprite *sprite);

