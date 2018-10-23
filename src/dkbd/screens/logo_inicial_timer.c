#include "logo_inicial.h"
#include "logo_inicial_private.h"

#include "../base/event_timer_handler.h"
#include "../io/joy_handlers.h"
#include "../util/palette.h"
#include "../base/lifecycle.h"

void logoInicial_onStartBegin();
void logoInicial_onStartPrepared();
void logoInicial_onStartCompleted();
void logoInicial_onExitBegin();
void logoInicial_onExitEndGraphics();
void logoInicial_onExitCompleted();

void logoInicial_beginStart() {
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(0,   logoInicial_onStartBegin);
	eventTimerHandler_addSlot(50,  logoInicial_onStartPrepared);
	eventTimerHandler_addSlot(100, logoInicial_onStartCompleted);
	eventTimerHandler_enable();
}

void logoInicial_beginExit() {
	lifecycle_resetUpdater();
	eventTimerHandler_reset();
	eventTimerHandler_addSlot(50,  logoInicial_onExitBegin);
	eventTimerHandler_addSlot(300, logoInicial_onExitEndGraphics);
	eventTimerHandler_addSlot(350, logoInicial_onExitCompleted);
	eventTimerHandler_enable();
	JOY_setEventHandler( &disabledJoyHandler );
}

void logoInicial_onStartBegin() {
	palette_fadeIn();
}

void logoInicial_onStartPrepared() {
	JOY_setEventHandler( &ingameKeyJoyHandler );
}

void logoInicial_onStartCompleted() {
	logoInicial_beginExit();
}

void logoInicial_onExitBegin() {
	VDP_fadeOut(0, 63, 30, TRUE);
	JOY_setEventHandler( &disabledJoyHandler );
}

void logoInicial_onExitEndGraphics() {
	logoInicial_finalizeGraphics();
}

void logoInicial_onExitCompleted() {
	logoInicial_finalizeMemory();
	lifecycle_openScreen_portada();
}
