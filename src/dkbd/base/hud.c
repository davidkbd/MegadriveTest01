#include "hud.h"

#include "../util/palette.h"
#include "../util/numbers.h"
#include "screens_global.h"

#include "../../../res/gfx.h"

// Podriamos hacerla puntero, pero no consume demasiado, veremos mas adelante
struct Hud_st {
	u8 timeDigits[4];
	u8 scoreDigits[5];
	u8 lifesDigits[2];
	u32 initialTimeMS;
	u16 secondsCount;
	u16 cachedScore;
	u8 cachedLifes;
} Hud_DATA;

void hud_onTime(u8* digits, u8 length);
void hud_onScore(u8* digits, u8 length);
void hud_onLifes(u8* digits, u8 length);
void hud_putScoreDigit(u8 digitPos, u8* digits, u8 numberLenght, u16 tileId1, u16 tileId2);

void hud_reset() {
	Hud_DATA.initialTimeMS = getTimeAsFix32(FALSE);
	Hud_DATA.secondsCount = 0;
	Hud_DATA.cachedLifes = Hud_DATA.cachedScore = 0;
	
	for (u8 i = 0; i < 4; ++i) {
		Hud_DATA.timeDigits[i] = 0;
	}
	for (u8 i = 0; i < 5; ++i) {
		Hud_DATA.scoreDigits[i] = 0;
	}
	for (u8 i = 0; i < 2; ++i) {
		Hud_DATA.lifesDigits[i] = 0;
	}
}

void hud_updateTimer() {
	u32 timeMillis = getTimeAsFix32(FALSE);
	u32 timeSecs = timeMillis / 1000;
	if (Hud_DATA.secondsCount != timeSecs) {
		Hud_DATA.secondsCount = timeSecs - Hud_DATA.initialTimeMS / 1000;
		numbers_toTimeMmss(hud_onTime, Hud_DATA.secondsCount);
	}
	if (Hud_DATA.secondsCount > 539) {
		palette_loadHud((timeMillis / 2) % 10);
		palette_apply();
	}
}

void hud_updateScore() {
	u16 score = screensGlobal_getScore();
	if (Hud_DATA.cachedScore != score) {
		Hud_DATA.cachedScore = score;
		numbers_toDigitBaseN(hud_onScore, 10, score);
	}
}

void hud_updateLifes() {
	u8 lifes = screensGlobal_getLifes();
	if (Hud_DATA.cachedLifes != lifes) {
		Hud_DATA.cachedLifes = lifes;
		numbers_toDigitBaseN(hud_onLifes, 10, lifes);
	}
}

u32 hud_getTimeSeconds() {
	return Hud_DATA.secondsCount;
}

u32 hud_getInitialTimeMS() {
	return Hud_DATA.initialTimeMS;
}

void hud_onTime(u8* digits, u8 length) {
	if (Hud_DATA.timeDigits[3] != digits[3]) {
		u8 pos = digits[3] * 16;
		VDP_loadTileData(&(hud_nums_tile.tiles[pos]),     G_TILEINDEX_HUD_TIME1,   1, FALSE);
		VDP_loadTileData(&(hud_nums_tile.tiles[pos + 8]), G_TILEINDEX_HUD_TIME1_B, 1, FALSE);
		Hud_DATA.timeDigits[3] = digits[3];
	}
	if (Hud_DATA.timeDigits[2] != digits[2]) {
		u8 pos = digits[2] * 16;
		VDP_loadTileData(&(hud_nums_tile.tiles[pos]),     G_TILEINDEX_HUD_TIME2,   1, FALSE);
		VDP_loadTileData(&(hud_nums_tile.tiles[pos + 8]), G_TILEINDEX_HUD_TIME2_B, 1, FALSE);
		Hud_DATA.timeDigits[2] = digits[2];
	}
	if (Hud_DATA.timeDigits[1] != digits[1]) {
		u8 pos = digits[1] * 16;
		VDP_loadTileData(&(hud_nums_tile.tiles[pos]),     G_TILEINDEX_HUD_TIME3,   1, FALSE);
		VDP_loadTileData(&(hud_nums_tile.tiles[pos + 8]), G_TILEINDEX_HUD_TIME3_B, 1, FALSE);
		Hud_DATA.timeDigits[1] = digits[1];

	}
	if (Hud_DATA.timeDigits[0] != digits[0]) {
		u8 pos = digits[0] * 16;
		VDP_loadTileData(&(hud_nums_tile.tiles[pos]),     G_TILEINDEX_HUD_TIME4,   1, FALSE);
		VDP_loadTileData(&(hud_nums_tile.tiles[pos + 8]), G_TILEINDEX_HUD_TIME4_B, 1, FALSE);
		Hud_DATA.timeDigits[0] = digits[0];
	}
}

void hud_onScore(u8* digits, u8 length) {
	hud_putScoreDigit(0, digits, length, G_TILEINDEX_HUD_SCORE5, G_TILEINDEX_HUD_SCORE5_B);
	hud_putScoreDigit(1, digits, length, G_TILEINDEX_HUD_SCORE4, G_TILEINDEX_HUD_SCORE4_B);
	hud_putScoreDigit(2, digits, length, G_TILEINDEX_HUD_SCORE3, G_TILEINDEX_HUD_SCORE3_B);
	hud_putScoreDigit(3, digits, length, G_TILEINDEX_HUD_SCORE2, G_TILEINDEX_HUD_SCORE2_B);
	hud_putScoreDigit(4, digits, length, G_TILEINDEX_HUD_SCORE1, G_TILEINDEX_HUD_SCORE1_B);
}

void hud_onLifes(u8* digits, u8 length) {
	if (length > 1 && Hud_DATA.lifesDigits[1] != digits[1]) {
		u8 pos = digits[1] * 16;
		VDP_loadTileData(&(hud_nums_tile.tiles[pos]),     G_TILEINDEX_HUD_LIFES1,   1, FALSE);
		VDP_loadTileData(&(hud_nums_tile.tiles[pos + 8]), G_TILEINDEX_HUD_LIFES1_B, 1, FALSE);
		Hud_DATA.lifesDigits[1] = digits[1];

	}
	if (Hud_DATA.lifesDigits[0] != digits[0]) {
		u8 pos = digits[0] * 16;
		VDP_loadTileData(&(hud_nums_tile.tiles[pos]),     G_TILEINDEX_HUD_LIFES2,   1, FALSE);
		VDP_loadTileData(&(hud_nums_tile.tiles[pos + 8]), G_TILEINDEX_HUD_LIFES2_B, 1, FALSE);
		Hud_DATA.lifesDigits[0] = digits[0];
	}
}

void hud_putScoreDigit(u8 digitPos, u8* digits, u8 numberLenght, u16 tileId1, u16 tileId2) {
	if (Hud_DATA.scoreDigits[digitPos] != digits[digitPos]) {
		u8 pos;
		if (numberLenght > digitPos) {
			pos = digits[digitPos] * 16;
		} else {
			pos = 0;
		}
		VDP_loadTileData(&(hud_nums_tile.tiles[pos]),     tileId1, 1, FALSE);
		VDP_loadTileData(&(hud_nums_tile.tiles[pos + 8]), tileId2, 1, FALSE);
		Hud_DATA.scoreDigits[digitPos] = digits[digitPos];
	}
}
