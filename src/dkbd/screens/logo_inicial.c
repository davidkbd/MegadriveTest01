#include "logo_inicial.h"
#include "logo_inicial_private.h"

#include "../base/event_timer_handler.h"

void logoInicial_update() {
	eventTimerHandler_update();
}

void logoInicial_initialize() {
	logoInicial_initUI();
	logoInicial_initMemory();
	logoInicial_initData();
	logoInicial_initSound();
	logoInicial_initPalete();
	logoInicial_initBackgrounds();
	logoInicial_initSprites();
	logoInicial_beginStart();
}
