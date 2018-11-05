#include <genesis.h>

#include "../util/vector2.h"
#include "../util/rect.h"

#include "../../../res/sprite.h"

#ifndef INGAMESPRITE_TYPE_H_
#define INGAMESPRITE_TYPE_H_

struct IngameSprite_Type_st {
	u8 isStatic;
	Vector2 size;
	u8 xCenter;
	u8 yCenter;
	Rect collider;
	Rect footsCollider;
	// Id de paleta a utilizar al crear
	u8 palette;
	// Datos del sprite fijados en sprite.res
	const SpriteDefinition *spriteDef;
};
typedef struct IngameSprite_Type_st IngameSprite_Type;

static const IngameSprite_Type INGAMESPRITE_PLAYER_TYPE =    {.isStatic = 0, {.x = 240, .y = 320}, .xCenter = 120, .yCenter = 160, .collider = {.pos1.x = -120, .pos1.y = -200, .pos2.x = 120, .pos2.y = 0}, .footsCollider = {.pos1.x =  -40, .pos1.y = -40, .pos2.x =  40, .pos2.y = 0}, .palette = PAL2, .spriteDef = &testingame_player};
static const IngameSprite_Type INGAMESPRITE_JUMPER_TYPE =    {.isStatic = 1, {.x = 240, .y = 240}, .xCenter = 120, .yCenter = 120, .collider = {.pos1.x =  -80, .pos1.y = -160, .pos2.x = 80,  .pos2.y = 0}, .footsCollider = {.pos1.x = -120, .pos1.y = -60, .pos2.x = 120, .pos2.y = 0}, .palette = PAL2, .spriteDef = &jumper};
static const IngameSprite_Type INGAMESPRITE_SPIKES_TYPE =    {.isStatic = 1, {.x = 240, .y = 240}, .xCenter = 120, .yCenter = 120, .collider = {.pos1.x =  -80, .pos1.y = -160, .pos2.x = 80,  .pos2.y = 0}, .footsCollider = {.pos1.x = -120, .pos1.y = -60, .pos2.x = 120, .pos2.y = 0}, .palette = PAL2, .spriteDef = &spikes};
static const IngameSprite_Type INGAMESPRITE_LEVELDOOR_TYPE = {.isStatic = 1, {.x = 240, .y = 320}, .xCenter = 120, .yCenter = 160, .collider = {.pos1.x =  -120, .pos1.y = -160, .pos2.x = 120,  .pos2.y = 0}, .footsCollider = {.pos1.x = -120, .pos1.y = -60, .pos2.x = 120, .pos2.y = 0}, .palette = PAL2, .spriteDef = &leveldoor};

#endif
