#include "portada.h"
#include "portada_private.h"

#include "../io/joy_handlers.h"
#include "../util/menu_list.h"

void portada_configureControlsMenu() {
	onKeyPressStartFunction   = portada_onKeyAcceptPressFunction;
	onKeyPressAFunction       = portada_onKeyAcceptPressFunction;
	onKeyPressBFunction       = portada_onKeyCancelPressFunction;
	onKeyPressCFunction       = portada_onKeyAcceptPressFunction;
	onKeyPressXFunction       = portada_onKeyNoneFunction;
	onKeyPressYFunction       = portada_onKeyNoneFunction;
	onKeyPressZFunction       = portada_onKeyNoneFunction;
	onKeyPressUpFunction      = portada_onKeyUpPressFunction;
	onKeyPressDownFunction    = portada_onKeyDownPressFunction;
	onKeyPressLeftFunction    = portada_onKeyNoneFunction;
	onKeyPressRightFunction   = portada_onKeyNoneFunction;
}

void portada_configureControlsPortada() {
	onKeyPressStartFunction   = portada_onKeyPressFunction;
	onKeyPressAFunction       = portada_onKeyNoneFunction;
	onKeyPressBFunction       = portada_onKeyNoneFunction;
	onKeyPressCFunction       = portada_onKeyNoneFunction;
	onKeyPressXFunction       = portada_onKeyNoneFunction;
	onKeyPressYFunction       = portada_onKeyNoneFunction;
	onKeyPressZFunction       = portada_onKeyNoneFunction;
	onKeyPressUpFunction      = portada_onKeyNoneFunction;
	onKeyPressDownFunction    = portada_onKeyNoneFunction;
	onKeyPressLeftFunction    = portada_onKeyNoneFunction;
	onKeyPressRightFunction   = portada_onKeyNoneFunction;
}

void portada_onKeyPressFunction(u16 joy) {
	portada_hidePressStart();
	portada_showMenu();
}

void portada_onKeyReleaseFunction(u16 joy) {
}

void portada_onKeyNoneFunction(u16 joy) {
}

void portada_onKeyUpPressFunction(u16 joy) {
	menuList_up();
}

void portada_onKeyDownPressFunction(u16 joy) {
	menuList_down();
}

void portada_onKeyAcceptPressFunction(u16 joy) {
	menuList_accept();
}

void portada_onKeyCancelPressFunction(u16 joy) {
	menuList_cancel();
}
