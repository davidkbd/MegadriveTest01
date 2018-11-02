#include "../base/screens_global.h"

#include "../base/ingame_sprite.h"

#include "../util/rect.h"
#include "../util/vector2.h"

#define IngamePlatforms_KEY_UP        0b00000001
#define IngamePlatforms_KEY_RIGHT     0b00000010
#define IngamePlatforms_KEY_DOWN      0b00000100
#define IngamePlatforms_KEY_LEFT      0b00001000
#define IngamePlatforms_KEY_JUMP      0b00010000
#define IngamePlatforms_KEY_ACTION    0b00100000

#define IngamePlatforms_DISABLEKEY_UP     0b11111110
#define IngamePlatforms_DISABLEKEY_RIGHT  0b11111101
#define IngamePlatforms_DISABLEKEY_DOWN   0b11111011
#define IngamePlatforms_DISABLEKEY_LEFT   0b11110111
#define IngamePlatforms_DISABLEKEY_JUMP   0b11101111
#define IngamePlatforms_DISABLEKEY_ACTION 0b11011111

#define IngamePlatforms_NUM_SPRITES 10

#define INGAME_PLATFORMS_MAX_X_SPEED 25
#define INGAME_PLATFORMS_JUMP_FORCE -70
#define INGAME_PLATFORMS_MAX_JUMP_SPEED -110
#define INGAME_PLATFORMS_MAX_FALLING_SPEED 70

#ifndef INGAME_PLATFORMS_PRIVATE_H
#define INGAME_PLATFORMS_PRIVATE_H

struct IngamePlatforms_ScreenData {
	struct ScreenData {
		u16 frameCount;
		u8 sceneAnimationFrame;
		Vector2 viewportOffset;
	} screenData;

	s8 gravity;

	IngameSprite hudTimeSprite;
	IngameSprite hudAnimalsSprite;
	IngameSprite hudScoreSprite;

	IngameSprite *playerSpritePTR;
	IngameSprite sprites[IngamePlatforms_NUM_SPRITES];
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
u8 ingamePlatforms_isPressingJump();
u8 ingamePlatforms_isPressingAction();

// Callback cuando el viewport encuentra sprites a crear
void ingamePlatforms_onViewportSprite(u8 spriteId, s16 x, s16 y);

// Callback de actualizacion del sprite del jugador
void ingamePlatforms_onPlayerUpdate(IngameSprite *sprite);
