#include <genesis.h>

#include "../base/screens_global.h"

void palette_loadGreenHill();
void palette_loadOtro();

u16 palette_array[64];

const u16 palette_hudColors[10][2] = {
	{ 0xfff, 0x222 },
	{ 0xccf, 0x222 },
	{ 0xaaf, 0x322 },
	{ 0x99e, 0x322 },
	{ 0x88d, 0x422 },
	{ 0x88d, 0x422 },
	{ 0x99e, 0x322 },
	{ 0xaaf, 0x322 },
	{ 0xccf, 0x322 },
	{ 0xfff, 0x222 }
};

u16 palette_rgb(u8 r, u8 g, u8 b) {
	return b * 16 * 16 + g * 16 + r;
}

void palette_write(u8 pal, u16* data) {
	// pal = PAL0 PAL1 PAL2 PAL3 (0, 1, 2, 3)
	// x 16, direccion de memoria de las 4 paletas
	// el 32 es porque el array son 16 posiciones, de U16 -> memcpy copia U8
	const u8 memPosition = pal * 16;
	memcpy(&palette_array[memPosition], data, 32);
}

void palette_putColor(u8 pal, u16 colorIndex, u16 color) {
	// pal = PAL0 PAL1 PAL2 PAL3 (0, 1, 2, 3)
	// x 16, direccion de memoria de las 4 paletas
	// el 32 es porque el array son 16 posiciones, de U16 -> memcpy copia U8
	const u8 memPosition = pal * 16;
	palette_array[memPosition + colorIndex] = color;
}

void palette_apply() {
	VDP_setPalette(PAL0, &(palette_array[0]));
	VDP_setPalette(PAL1, &(palette_array[16]));
	VDP_setPalette(PAL2, &(palette_array[32]));
	VDP_setPalette(PAL3, &(palette_array[48]));
}

void palette_fadeIn() {
	VDP_fadeIn(0, 63, palette_array, 120, FALSE);
}

void palette_loadScreen(u8 screenId) {
	switch (screenId) {
		case 0: palette_loadGreenHill(); break;
		case 1: palette_loadOtro(); break;
	}
}

void palette_loadHud(u8 status) {
	palette_putColor(PAL1, 1, 0x000);
	palette_putColor(PAL1, 2, 0xccc);
	palette_putColor(PAL1, 14, palette_hudColors[status][0]);
	palette_putColor(PAL1, 15, palette_hudColors[status][1]);
}

void palette_loadEnemies(u8 type) {
}

void palette_loadGreenHill() {
	palette_putColor(PAL0, 1, 0x0); // Bordes
	palette_putColor(PAL0, 2, 0x262);
	palette_putColor(PAL0, 3, 0x07B);
	palette_putColor(PAL0, 4, 0x141);
	palette_putColor(PAL0, 5, 0x059);
	palette_putColor(PAL0, 6, 0x374); // Bordes1
	palette_putColor(PAL0, 7, 0x396); // Bordes2
	palette_putColor(PAL0, 8, 0x05b); // Detalles1 Marron
	palette_putColor(PAL0, 9, 0x07f); // Detalles2 Marron
	palette_putColor(PAL0, 10, 0x0ff); // Detalles3 Marron
	palette_putColor(PAL0, 11, 0x4a7); // Detalles3 Verde
	palette_putColor(PAL0, 12, 0x005); // Roca Base
	palette_putColor(PAL0, 13, 0x259); // Roca Base
	palette_putColor(PAL0, 14, 0x27b); // Roca Base
	palette_putColor(PAL0, 15, 0x7cf); //

	palette_putColor(PAL3, 1, 0x722); // Agua
	palette_putColor(PAL3, 2, 0xa66);
	palette_putColor(PAL3, 3, 0x944);
	palette_putColor(PAL3, 4, 0x833);
	palette_putColor(PAL3, 5, 0x722);
}

void palette_loadOtro() {
	palette_putColor(PAL0, 1, 0x0);
	palette_putColor(PAL0, 2, 0x262);
	palette_putColor(PAL0, 3, 0x07B);
	palette_putColor(PAL0, 4, 0x141);
	palette_putColor(PAL0, 5, 0x059);
	palette_putColor(PAL0, 6, 0x374);
	palette_putColor(PAL0, 7, 0x396);
	palette_putColor(PAL0, 8, 0x05b);
	palette_putColor(PAL0, 9, 0x07f);
	palette_putColor(PAL0, 10, 0x0ff);

	palette_putColor(PAL3, 1, 0x722); // Agua
	palette_putColor(PAL3, 2, 0xa66);
	palette_putColor(PAL3, 3, 0x944);
	palette_putColor(PAL3, 4, 0x833);
	palette_putColor(PAL3, 5, 0x722);
}
