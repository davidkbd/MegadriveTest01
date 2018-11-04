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
		TitleScreen_DATA->positions[i] = viewport_getCurrentY() + 60;
		TitleScreen_DATA->letters[i] = SPR_addSpriteEx(&title_letter,
				viewport_getCurrentX(),
				viewport_getCurrentY(),
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
	++TitleScreen_DATA->timer;
	if (TitleScreen_DATA->timer == 159) {
		titleScreen_finalize();
		return;
	}

	if (TitleScreen_DATA->timer < 20 || TitleScreen_DATA->timer > 150) {
		for (u8 i = 0; i < 10; ++i) {
			TitleScreen_DATA->positions[i] += 4;
			SPR_setPosition(TitleScreen_DATA->letters[i],
					viewport_getCurrentX() + i*16 + 80,
					TitleScreen_DATA->positions[i]);
		}
	}
}

void titleScreen_finalize() {
	for (u8 i = 0; i < 10; ++i) {
		SPR_releaseSprite(TitleScreen_DATA->letters[i]);
	}
	MEM_free(TitleScreen_DATA);
}
