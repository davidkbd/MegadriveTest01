#include "portada.h"
#include "portada_private.h"

#include "../base/configuration.h"
#include "../base/event_timer_handler.h"
#include "../util/menu_list.h"
#include "../util/limits.h"

void portada_configureMenu1(u8 o);
void portada_configureMenu2(u8 o);
void portada_menuPlay(u8 o);
void portada_menu_acceptOption(u8 o);
void portada_menu_cancelOption(u8 o);
void portada_menu_backToTitle(u8 o);

void portada_showMenu() {
	portada_configureControlsMenu();
	portada_configureMenu1(0);
}

void portada_configureMenu1(u8 o) {
	u32 cont1[3] = {
		Portada_DATA->tileMenuPlayIndex,
		Portada_DATA->tileMenuOptionsIndex,
		MenuList_ENDMENU };
	MenuList_EventCallback acc1[2] = {
		portada_menuPlay,
		portada_configureMenu2 };
	MenuList_EventCallback cnl1[2] = {
		portada_menu_backToTitle,
		portada_menu_backToTitle };

	menuList_destroy();
	menuList_initialize(cont1, acc1, cnl1, 1);
	menuList_setOnRepaintFunction(portada_onRepaintMenu);
}

void portada_configureMenu2(u8 o) {
	u32 cont1[6] = {
		Portada_DATA->tileMenuMusicIndex,
		Portada_DATA->tileMenuSfxIndex,
		Portada_DATA->tileMenuDifficultIndex,
		Portada_DATA->tileMenuDifficultIndex,
		Portada_DATA->tileMenuBackIndex,
		MenuList_ENDMENU };
	MenuList_EventCallback acc1[5] = {
		portada_menu_acceptOption,
		portada_menu_acceptOption,
		portada_menu_acceptOption,
		portada_menu_acceptOption,
		portada_configureMenu1 };
	MenuList_EventCallback cnl1[5] = {
		portada_menu_cancelOption,
		portada_menu_cancelOption,
		portada_menu_cancelOption,
		portada_menu_cancelOption,
		portada_configureMenu1 };

	menuList_destroy();
	menuList_initialize(cont1, acc1, cnl1, 2);
	menuList_setOnRepaintFunction(portada_onRepaintMenu);
}

void portada_menuPlay(u8 o) {
	portada_beginExit();
}

void portada_menu_acceptOption(u8 o) {
	if (o == Portada_DATA->tileMenuMusicIndex) {
		configuration_setMusicEnabled(1);
	} else if (o == Portada_DATA->tileMenuSfxIndex) {
		configuration_setSfxEnabled(1);
	} else if (o == Portada_DATA->tileMenuDifficultIndex) {
		configuration_setDifficulty(limits_incr_s8(configuration_getDifficulty(), 1, 0, 3));
	}
}

void portada_menu_cancelOption(u8 o) {
	if (o == Portada_DATA->tileMenuMusicIndex) {
		configuration_setMusicEnabled(0);
	} else if (o == Portada_DATA->tileMenuSfxIndex) {
		configuration_setSfxEnabled(0);
	} else if (o == Portada_DATA->tileMenuDifficultIndex) {
		configuration_setDifficulty(limits_incr_s8(configuration_getDifficulty(), -1, 0, 3));
	}
}

void portada_menu_backToTitle(u8 o) {
	portada_configureControlsPortada();
	portada_showPressStart();
	menuList_destroy();
}
