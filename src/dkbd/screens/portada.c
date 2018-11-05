#include <genesis.h>

#include "portada.h"
#include "portada_private.h"

#include "../base/configuration.h"
#include "../base/event_timer_handler.h"
#include "../util/menu_list.h"

void portada_update() {
	eventTimerHandler_update();
	menuList_refresh();
}

void portada_initialize() {
	portada_initUI();
	portada_initMemory();
	portada_initData();
	portada_initSound();
	portada_initPalete();
	portada_initBackgrounds();
	portada_initSprites();
	portada_beginStart();
}

void portada_onRepaintMenu(u8 selected, u32 *content, u32 info) {
	for (int i=0; i<6; ++i) {
		for (int j=0; j<9; ++j) {
			VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL3, TRUE, 0, 0, G_TILEINDEX_CHARSET), 16+j, 20+i);
		}
	}
	int i=0;
	while(content[i] != MenuList_ENDMENU) {
		u32 incr = (i == selected) ? 8 : 0;
		u32 item = content[i] + incr;
		for (int j=0; j<8; ++j) {
			VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL3, TRUE, 0, 0, item+j), 16+j, 20+i);
		}
		++i;
	}
	if (info == 2) {
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL3, TRUE, 0, 0, Portada_DATA->tileYesNoIndex + configuration_isMusicEnabled()), 24, 20);
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL3, TRUE, 0, 0, Portada_DATA->tileYesNoIndex + configuration_isSfxEnabled()), 24, 21);
		VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL3, TRUE, 0, 0, Portada_DATA->tileDifficultyIndex + configuration_getDifficulty()), 24, 22);
	}
}

void portada_showPressStart() {
	for (int i=0; i<6; ++i) {
		for (int j=0; j<9; ++j) {
			VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL3, TRUE, 0, 0, G_TILEINDEX_CHARSET), 16+j, 20+i);
		}
	}
	SPR_setPosition(Portada_DATA->sprites[1], 160 - 64, 180);
}

void portada_hidePressStart() {
	SPR_setPosition(Portada_DATA->sprites[1], 160 - 64, 480);
}

