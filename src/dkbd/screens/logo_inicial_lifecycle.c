#include "logo_inicial.h"
#include "logo_inicial_private.h"

#include "../util/palette.h"

#include "../../../res/sprite.h"
#include "../../../res/gfx.h"

// ================ INIT ================ //

void logoInicial_initUI() {
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setHorizontalScroll(PLAN_A, 0);
	VDP_setHorizontalScroll(PLAN_B, 0);
	//VDP_setWindowHPos(FALSE, 0);
	//VDP_setWindowVPos(FALSE, 0);
}

void logoInicial_initMemory() {
	LogoInicial_DATA = MEM_alloc(sizeof(struct LogoInicial_Data_st));
}

void logoInicial_initData() {
}

void logoInicial_initSound() {
}

void logoInicial_initPalete() {
	VDP_setPaletteColors(0, (u16*) palette_black, 64);
	palette_write(PAL0, logoinicial_logo.palette->data);
}

void logoInicial_initBackgrounds() {
}

void logoInicial_initSprites() {
	LogoInicial_DATA->sprites[0] = SPR_addSprite(&logoinicial_logo, 160 - 64, 40, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
	SPR_setAnim(LogoInicial_DATA->sprites[0], 0);
	SPR_update();
}

// ================ FINALIZE ================ //

void logoInicial_finalizeGraphics() {
	for (int i=0; i<LogoInicial_NUM_SPRITES; ++i) {
		SPR_releaseSprite(LogoInicial_DATA->sprites[i]);
	}
	VDP_clearTextArea(0, 0, 39, 27);
}

void logoInicial_finalizeMemory() {
	MEM_free(LogoInicial_DATA);
}
