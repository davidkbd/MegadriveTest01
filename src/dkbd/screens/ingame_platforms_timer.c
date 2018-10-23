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
void ingamePlatforms_onExitEndGraphics();
void ingamePlatforms_onExitCompleted();

void ingamePlatforms_beginStart() {
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(0,   ingamePlatforms_onStartBegin);
	eventTimerHandler_addSlot(50,  ingamePlatforms_onStartPrepared);
	eventTimerHandler_addSlot(100, ingamePlatforms_onStartCompleted);
	eventTimerHandler_enable();
}

void ingamePlatforms_beginExit() {
	lifecycle_resetUpdater();
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(50,  ingamePlatforms_onExitBegin);
	eventTimerHandler_addSlot(300, ingamePlatforms_onExitEndGraphics);
	eventTimerHandler_addSlot(350, ingamePlatforms_onExitCompleted);
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

void ingamePlatforms_onExitEndGraphics() {
	ingamePlatforms_finalizeGraphics();
}

void ingamePlatforms_onExitCompleted() {
	ingamePlatforms_finalizeMemory();
	lifecycle_openScreen_logoInicial();
}
