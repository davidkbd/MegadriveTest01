#include "portada.h"
#include "portada_private.h"

#include "../base/event_timer_handler.h"
#include "../base/lifecycle.h"
#include "../io/joy_handlers.h"
#include "../util/menu_list.h"
#include "../util/palette.h"

void portada_onStartBegin();
void portada_onStartPrepared();
void portada_onStartCompleted();
void portada_onExitBegin();
void portada_onExitEndGraphics();
void portada_onExitCompleted();

void portada_beginStart() {
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(0,   portada_onStartBegin);
	eventTimerHandler_addSlot(50,  portada_onStartPrepared);
	eventTimerHandler_addSlot(110, portada_onStartCompleted);
	eventTimerHandler_enable();
}

void portada_beginExit() {
	menuList_destroy();
	lifecycle_resetUpdater();
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(50,  portada_onExitBegin);
	eventTimerHandler_addSlot(300, portada_onExitEndGraphics);
	eventTimerHandler_addSlot(350, portada_onExitCompleted);
	eventTimerHandler_enable();
	JOY_setEventHandler( &disabledJoyHandler );
}

void portada_onStartBegin() {
	palette_fadeIn();
}

void portada_onStartPrepared() {
	JOY_setEventHandler( &ingameKeyJoyHandler );
	portada_configureControlsPortada();
	portada_showPressStart();
}

void portada_onStartCompleted() {
}

void portada_onExitBegin() {
	VDP_fadeOut(0, 63, 30, TRUE);
}

void portada_onExitEndGraphics() {
	portada_finalizeGraphics();
}

void portada_onExitCompleted() {
	portada_finalizeMemory();
	lifecycle_openScreen_ingame_platforms();
}

