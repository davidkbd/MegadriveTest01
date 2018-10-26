#include "../base/screens_global.h"

#include "../util/rect.h"
#include "../util/vector2.h"

#define IngamePlatforms_KEY_UP     0b00001
#define IngamePlatforms_KEY_RIGHT  0b00010
#define IngamePlatforms_KEY_DOWN   0b00100
#define IngamePlatforms_KEY_LEFT   0b01000
#define IngamePlatforms_KEY_JUMP   0b10000

#define IngamePlatforms_NOKEY_UP     0b11110
#define IngamePlatforms_NOKEY_RIGHT  0b11101
#define IngamePlatforms_NOKEY_DOWN   0b11011
#define IngamePlatforms_NOKEY_LEFT   0b10111
#define IngamePlatforms_NOKEY_JUMP   0b01111

#define IngamePlatforms_NUM_SPRITES 3

#define INGAME_PLATFORMS_MAX_X_SPEED 34
#define INGAME_PLATFORMS_JUMP_FORCE -80
#define INGAME_PLATFORMS_MAX_FALLING_SPEED 70

#ifndef INGAME_PLATFORMS_PRIVATE_H
#define INGAME_PLATFORMS_PRIVATE_H

struct IngamePlatforms_Sprite_st {
	const SpriteDefinition *spriteDef;
	u8 alwaysOnTop;
	Sprite* sprite;
	Vector2 position;
	Vector2 posInViewport;
	Vector2 speed;
	Vector2 size; // Visualmente, utilizado para saber si cargar o destruir al hacer scroll
	u8 onFloor;
	u8 xCenter;
	Rect collider;
	//0xFFFF
	u16 data;
	//Callback de actualizacion
	void (*update)(struct IngamePlatforms_Sprite_st *sprite);
};
typedef struct IngamePlatforms_Sprite_st IngamePlatforms_Sprite;

struct IngamePlatforms_ScreenData {
	struct ScreenData {
		u16 frameCount;
		u8 sceneAnimationFrame;
	} screenData;

	s8 gravity;

	IngamePlatforms_Sprite hudTimeSprite;
	IngamePlatforms_Sprite hudAnimalsSprite;
	IngamePlatforms_Sprite hudScoreSprite;

	IngamePlatforms_Sprite *playerSpritePTR;
	IngamePlatforms_Sprite sprites[IngamePlatforms_NUM_SPRITES];
};
struct IngamePlatforms_ScreenData* IngamePlatforms_DATA;

#endif

void ingamePlatforms_initUI();
void ingamePlatforms_initMemory();
void ingamePlatforms_initData();
void ingamePlatforms_initSound();
void ingamePlatforms_initPalete();
void ingamePlatforms_initBackgrounds();
void ingamePlatforms_initSprites();
void ingamePlatforms_finalizeSound();
void ingamePlatforms_finalizeGraphics();
void ingamePlatforms_finalizeMemory();

void ingamePlatforms_beginStart();
void ingamePlatforms_beginExit();

void ingamePlatforms_updateControls();

u8 ingamePlatforms_isPressingUp();
u8 ingamePlatforms_isPressingLeft();
u8 ingamePlatforms_isPressingRight();
u8 ingamePlatforms_isPressingDown();
u8 ingamePlatforms_isPresingJump();

void ingamePlatforms_onPlayerUpdate(IngamePlatforms_Sprite *sprite);
