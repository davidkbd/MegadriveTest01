#include "../base/screens_global.h"

#include "../util/rect.h"
#include "../util/vector2.h"

#define TestIngame_KEY_UP     0b00001
#define TestIngame_KEY_RIGHT  0b00010
#define TestIngame_KEY_DOWN   0b00100
#define TestIngame_KEY_LEFT   0b01000
#define TestIngame_IN_AIR     0b10000

#define TestIngame_NOKEY_UP     0b11110
#define TestIngame_NOKEY_RIGHT  0b11101
#define TestIngame_NOKEY_DOWN   0b11011
#define TestIngame_NOKEY_LEFT   0b10111
#define TestIngame_NOIN_AIR     0b01111	

#define TestIngame_NUM_SPRITES 3

#ifndef TESTINGAME_PRIVATE_H
#define TESTINGAME_PRIVATE_H

struct TestIngame_Sprite_st {
	const SpriteDefinition *spriteDef;
	u8 alwaysOnTop;
	Sprite* sprite;
	Vector2 position;
	Vector2 posInViewport;
	Vector2 size; // Visualmente, utilizado para saber si cargar o destruir al hacer scroll
	u8 xCenter;
	Rect collider;
	//0xFFFF
	u16 data;
	//Callback de actualizacion
	void (*update)(struct TestIngame_Sprite_st *sprite);
};
typedef struct TestIngame_Sprite_st TestIngame_Sprite;

struct TestIngame_ScreenData {
	struct ScreenData {
		u16 frameCount;
		u8 sceneAnimationFrame;
	} screenData;

	struct PlayerData {
		s8 xSpeed;
		s8 ySpeed;
	} playerData;

	TestIngame_Sprite hudTimeSprite;
	TestIngame_Sprite hudAnimalsSprite;
	TestIngame_Sprite hudScoreSprite;

	TestIngame_Sprite *playerSpritePTR;
	TestIngame_Sprite sprites[TestIngame_NUM_SPRITES];
};
struct TestIngame_ScreenData* TestIngame_DATA;

#endif

void testIngame_initUI();
void testIngame_initMemory();
void testIngame_initData();
void testIngame_initSound();
void testIngame_initPalete();
void testIngame_initBackgrounds();
void testIngame_initSprites();
void testIngame_finalizeSound();
void testIngame_finalizeGraphics();
void testIngame_finalizeMemory();

void testIngame_beginStart();
void testIngame_beginExit();

void testIngame_updateControls();

u8 testIngame_isPressingUp();
u8 testIngame_isPressingLeft();
u8 testIngame_isPressingRight();
u8 testIngame_isPressingDown();

void testIngame_onPlayerUpdate(TestIngame_Sprite *sprite);
