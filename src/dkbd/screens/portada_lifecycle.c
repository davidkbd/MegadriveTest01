#include "portada.h"
#include "portada_private.h"

#include "../util/palette.h"

#include "../../../res/sprite.h"
#include "../../../res/gfx.h"

// ================ INIT ================ //

void portada_initUI() {
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setHorizontalScroll(PLAN_A, 0);
	VDP_setHorizontalScroll(PLAN_B, 0);
	//VDP_setWindowHPos(FALSE, 0);
	//VDP_setWindowVPos(FALSE, 0);
}

void portada_initMemory() {
	Portada_DATA = MEM_alloc(sizeof(struct Portada_Data_st));
}

void portada_initData() {
}

void portada_initSound() {
}

void portada_initPalete() {
	VDP_setPaletteColors(0, (u16*) palette_black, 64);
	palette_write(PAL0, portada_press.palette->data);
	palette_write(PAL1, portada_portada.palette->data);
	palette_write(PAL2, portada_press.palette->data);
	palette_write(PAL3, portada_opts_palete.palette->data);
}

void portada_initBackgrounds() {
	VDP_drawImageEx(PLAN_B, &planb_level01, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_TILEINDEX_PLANB), 0, 0, TRUE, FALSE);
}

void portada_initSprites() {
	Portada_DATA->tileUserIndex = TILE_USERINDEX;

	Portada_DATA->tileMenuIndex = Portada_DATA->tileUserIndex;
	VDP_loadTileData(portada_menu_tile.tiles, Portada_DATA->tileMenuIndex, portada_menu_tile.numTile, FALSE);
	Portada_DATA->tileUserIndex += portada_menu_tile.numTile;

	Portada_DATA->tileMenuPlayIndex      = Portada_DATA->tileMenuIndex + 0;
	Portada_DATA->tileMenuOptionsIndex   = Portada_DATA->tileMenuIndex + 16;
	Portada_DATA->tileMenuMusicIndex     = Portada_DATA->tileMenuIndex + 32;
	Portada_DATA->tileMenuSfxIndex       = Portada_DATA->tileMenuIndex + 48;
	Portada_DATA->tileMenuDifficultIndex = Portada_DATA->tileMenuIndex + 64;
	Portada_DATA->tileMenuBackIndex      = Portada_DATA->tileMenuIndex + 96;

	Portada_DATA->tileYesNoIndex = Portada_DATA->tileUserIndex;
	VDP_loadTileData(portada_yesno_tile.tiles, Portada_DATA->tileYesNoIndex, portada_yesno_tile.numTile, FALSE);
	Portada_DATA->tileUserIndex += portada_yesno_tile.numTile;

	Portada_DATA->tileDifficultyIndex = Portada_DATA->tileUserIndex;
	VDP_loadTileData(portada_difficulty_tile.tiles, Portada_DATA->tileDifficultyIndex, portada_difficulty_tile.numTile, FALSE);
	Portada_DATA->tileUserIndex += portada_difficulty_tile.numTile;

	Portada_DATA->sprites[0] = SPR_addSprite(&portada_portada, 160 - 64, 40, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
	SPR_setAnim(Portada_DATA->sprites[0], 0);

	Portada_DATA->sprites[1] = SPR_addSprite(&portada_press, 160 - 64, 480, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
	SPR_setAnim(Portada_DATA->sprites[1], 0);
}

// ================ FINALIZE ================ //

void portada_finalizeGraphics() {
	for (int i=0; i<Portada_NUM_SPRITES; ++i) {
		SPR_releaseSprite(Portada_DATA->sprites[i]);
	}
}

void portada_finalizeMemory() {
	MEM_free(Portada_DATA);
}
