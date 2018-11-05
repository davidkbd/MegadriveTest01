#include "ingame_platforms.h"
#include "ingame_platforms_private.h"

#include "../base/event_timer_handler.h"
#include "../base/lifecycle.h"
#include "../base/hud.h"
#include "../base/viewport.h"
#include "../io/joy_handlers.h"
#include "../util/palette.h"

void ingamePlatforms_onStartBegin();
void ingamePlatforms_onStartCompleted();
void ingamePlatforms_onStartFinished();
void ingamePlatforms_onExitBegin();
void ingamePlatforms_onExitCompleted();

void ingamePlatforms_beginStart() {
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(0,   ingamePlatforms_onStartBegin);
	eventTimerHandler_addSlot(200, ingamePlatforms_onStartCompleted);
	eventTimerHandler_addSlot(260, ingamePlatforms_onStartFinished);
	eventTimerHandler_enable();
}

void ingamePlatforms_beginExit() {
	lifecycle_resetUpdater();
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(5,  ingamePlatforms_onExitBegin);
	eventTimerHandler_addSlot(50, ingamePlatforms_onExitCompleted);
	eventTimerHandler_enable();
	JOY_setEventHandler( &disabledJoyHandler );
}

void ingamePlatforms_onStartBegin() {
	palette_fastFadeIn();
}

void ingamePlatforms_onStartCompleted() {
	hud_reset();
	JOY_setEventHandler( &ingameKeyJoyHandler );
	viewport_refreshCurrentViewport();
	IngamePlatforms_DATA->hudTimeSprite.sprite    = SPR_addSpriteEx(&hud_time,    5,   3,   TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_TIME1),  0, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	IngamePlatforms_DATA->hudScoreSprite.sprite   = SPR_addSpriteEx(&hud_score,   5,   19,  TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_SCORE1), 1, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	IngamePlatforms_DATA->hudAnimalsSprite.sprite = SPR_addSpriteEx(&hud_animals, 265, 202, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_ITEMS1), 2, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	IngamePlatforms_DATA->hudLifesSprite.sprite   = SPR_addSpriteEx(&hud_lifes,   5,   202, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_LIFES),  3, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	IngamePlatforms_DATA->ingame_updatePtr = ingamePlatforms_update_postTitleScreen;
}

void ingamePlatforms_onStartFinished() {
	IngamePlatforms_DATA->ingame_updatePtr = ingamePlatforms_update_ingame;
}

void ingamePlatforms_onExitBegin() {
	VDP_fadeOut(0, 63, 30, TRUE);
	ingamePlatforms_finalizeSound();
}

void ingamePlatforms_onExitCompleted() {
	u16 levelDoorData = IngamePlatforms_DATA->sprites[16].data;
	ingamePlatforms_finalizeGraphics();
	ingamePlatforms_finalizeMemory();
	if (screensGlobal_getLifes() == 0) {
		screensGlobal_finalize();
		lifecycle_openScreen_logoInicial();
		return;
	}

	if (levelDoorData == 0) {
		screensGlobal_setLifes(screensGlobal_getLifes() - 1);
		lifecycle_openScreen_ingame_platforms();
		return;
	}

	lifecycle_openScreen_ingame_platforms();
}
