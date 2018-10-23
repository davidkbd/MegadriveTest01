#include "testingame.h"
#include "testingame_private.h"

#include "../base/event_timer_handler.h"
#include "../base/lifecycle.h"
#include "../base/hud.h"
#include "../io/joy_handlers.h"
#include "../util/palette.h"

void testIngame_onStartBegin();
void testIngame_onStartPrepared();
void testIngame_onStartCompleted();
void testIngame_onExitBegin();
void testIngame_onExitEndGraphics();
void testIngame_onExitCompleted();

void testIngame_beginStart() {
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(0,   testIngame_onStartBegin);
	eventTimerHandler_addSlot(50,  testIngame_onStartPrepared);
	eventTimerHandler_addSlot(100, testIngame_onStartCompleted);
	eventTimerHandler_enable();
}

void testIngame_beginExit() {
	lifecycle_resetUpdater();
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(50,  testIngame_onExitBegin);
	eventTimerHandler_addSlot(300, testIngame_onExitEndGraphics);
	eventTimerHandler_addSlot(350, testIngame_onExitCompleted);
	eventTimerHandler_enable();
	JOY_setEventHandler( &disabledJoyHandler );
}

void testIngame_onStartBegin() {
	palette_fadeIn();
}

void testIngame_onStartPrepared() {
	// Se puede usar para lanzar algo, algun titulo o algo...
}

void testIngame_onStartCompleted() {
	hud_init();
	JOY_setEventHandler( &ingameKeyJoyHandler );
}

void testIngame_onExitBegin() {
	VDP_fadeOut(0, 63, 30, TRUE);
	testIngame_finalizeSound();
}

void testIngame_onExitEndGraphics() {
	testIngame_finalizeGraphics();
}

void testIngame_onExitCompleted() {
	testIngame_finalizeMemory();
	lifecycle_openScreen_logoInicial();
}
