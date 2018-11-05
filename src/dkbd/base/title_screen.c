#include "title_screen.h"

#include "viewport.h"
#include "screens_global.h"
#include "../util/string.h"

#include "../../../res/sprite.h"

void titleScreen_finalize();

void titleScreen_initialize(const char *text) {
	TitleScreen_DATA = MEM_alloc(sizeof(struct TitleScreen_DATA_st));
	TitleScreen_DATA->timer = 0;
	const u8 titleLength = string_length(text);
	for (u8 i = 0; i < 10; ++i) {
		TitleScreen_DATA->positions[i] = 50;
		TitleScreen_DATA->letters[i] = SPR_addSpriteEx(&title_letter,
				-20,
				0,
				TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, G_TILEINDEX_LETTERS+i*4),
				79 - i,
				SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
		if (i < titleLength) {
			char c = text[i];
			if (c == ' ') {
				c = 0;
			} else {
				c -= 'a';
				++c;
			}
			SPR_setAnim(TitleScreen_DATA->letters[i], c);
		} else {
			SPR_setAnim(TitleScreen_DATA->letters[i], 0);
		}
	}
}

void titleScreen_update() {
	if (TitleScreen_DATA == 0) {
		return;
	}

	++TitleScreen_DATA->timer;
	if (TitleScreen_DATA->timer == 249) {
		titleScreen_finalize();
		return;
	}

	if (TitleScreen_DATA->timer < 20) {
		for (u8 i = 0; i < 10; ++i) {
			TitleScreen_DATA->positions[i] += 4;
		}
	} else if (TitleScreen_DATA->timer > 190) {
		for (u8 i = 0; i < 10; ++i) {
			TitleScreen_DATA->positions[i] += sinFix16(i * 20) / 4;
		}
	}
	fix16 y;
	for (u8 i = 0; i < 10; ++i) {
		y = TitleScreen_DATA->positions[i] + sinFix16(i * 2 + TitleScreen_DATA->timer * 5);
		if (y > 250 || y < 0) {
			y = 250;
		}
		SPR_setPosition(TitleScreen_DATA->letters[i],
				i*16 + 140,
				y);
	}
}

void titleScreen_finalize() {
	for (u8 i = 0; i < 10; ++i) {
		SPR_releaseSprite(TitleScreen_DATA->letters[i]);
	}
	MEM_free(TitleScreen_DATA);
	TitleScreen_DATA = 0;

}
