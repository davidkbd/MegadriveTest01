#include "../base/lifecycle.h"

#include "ingame_key_joy_handler_private.h"
#include "ingame_key_joy_handler.h"

void ingameKeyJoyHandler(u16 joy, u16 changed, u16 state) {
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_A,     onKeyPressAFunction,     onKeyReleaseAFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_B,     onKeyPressBFunction,     onKeyReleaseBFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_C,     onKeyPressCFunction,     onKeyReleaseCFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_X,     onKeyPressXFunction,     onKeyReleaseXFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_Y,     onKeyPressYFunction,     onKeyReleaseYFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_Z,     onKeyPressZFunction,     onKeyReleaseZFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_UP,    onKeyPressUpFunction,    onKeyReleaseUpFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_DOWN,  onKeyPressDownFunction,  onKeyReleaseDownFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_LEFT,  onKeyPressLeftFunction,  onKeyReleaseLeftFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_RIGHT, onKeyPressRightFunction, onKeyReleaseRightFunction);
	ingameKeyJoyHandler_checkAndExec(joy, state, changed, BUTTON_START, onKeyPressStartFunction, onKeyReleaseStartFunction);
}

// otras funciones interesante
// JOY_update() refresca el estado del pad, se llama en cada refresco de la pantalla
// JOY_readJoypad( joy ) Â¨devuelve el estado del pad1
// JOY_waitPressBtn() espera a que se pulse un boton (no direcciones)
// JOY_waitPress(joy, BUTTON_A | BUTTON_UP) espera a pulsar un boton indicado en un pad especifico

void ingameKeyJoyHandler_checkAndExec(u16 joy, u16 state, u16 changed, u16 key, void(*pressFunction)(u16), void(*releaseFunction)(u16)) {
	if (changed & key) {
		if (state & key) {
			pressFunction(joy);
		} else {
			releaseFunction(joy);
		}
	}
}
