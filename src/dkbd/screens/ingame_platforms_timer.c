#include "ingame_platforms.h"
#include "ingame_platforms_private.h"

#include "../base/event_timer_handler.h"
#include "../base/lifecycle.h"
#include "../base/hud.h"
#include "../io/joy_handlers.h"
#include "../util/palette.h"

void ingamePlatforms_onStartBegin();
void ingamePlatforms_onStartPrepared();
void ingamePlatforms_onStartCompleted();
void ingamePlatforms_onExitBegin();
void ingamePlatforms_onExitCompleted();

void ingamePlatforms_beginStart() {
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(0,   ingamePlatforms_onStartBegin);
	eventTimerHandler_addSlot(40,  ingamePlatforms_onStartPrepared);
	eventTimerHandler_addSlot(50,  ingamePlatforms_onStartCompleted);
	eventTimerHandler_enable();
}

void ingamePlatforms_beginExit() {
	lifecycle_resetUpdater();
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(50,  ingamePlatforms_onExitBegin);
	eventTimerHandler_addSlot(150, ingamePlatforms_onExitCompleted);
	eventTimerHandler_enable();
	JOY_setEventHandler( &disabledJoyHandler );
}

void ingamePlatforms_onStartBegin() {
	palette_fadeIn();
}

void ingamePlatforms_onStartPrepared() {
	// Se puede usar para lanzar algo, algun titulo o algo...
}

void ingamePlatforms_onStartCompleted() {
	hud_init();
	JOY_setEventHandler( &ingameKeyJoyHandler );
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
