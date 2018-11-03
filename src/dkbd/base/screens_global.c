#include "screens_global.h"

#include "configuration.h"

#include "../maps/level01.h"
#include "../maps/level01_sprites.h"

struct ScreensGlobal_DATA_st {
	u8 currentStage;
	u16 score;
	u8 lifes;
} * ScreensGlobal_DATA;

void screensGlobal_initialize() {
	ScreensGlobal_DATA = MEM_alloc(sizeof(struct ScreensGlobal_DATA_st));
	ScreensGlobal_DATA->currentStage = 1;
	ScreensGlobal_DATA->score = 0;
	switch (configuration_getDifficulty()) {
	case 0:
		ScreensGlobal_DATA->lifes = 10;
		break;
	case 1:
		ScreensGlobal_DATA->lifes = 5;
		break;
	case 2:
		ScreensGlobal_DATA->lifes = 2;
		break;
	}
}

void screensGlobal_finalize() {
	MEM_free(ScreensGlobal_DATA);
}

void screensGlobal_setCurrentStage(u8 p) {
	ScreensGlobal_DATA->currentStage = p;
}

void screensGlobal_setScore(u16 p) {
	ScreensGlobal_DATA->score = p;
}

void screensGlobal_setLifes(u8 p) {
	ScreensGlobal_DATA->lifes = p;
}

u8 screensGlobal_getCurrentStage() {
	return ScreensGlobal_DATA->currentStage;
}

u16 screensGlobal_getScore() {
	return ScreensGlobal_DATA->score;
}

u8 screensGlobal_getLifes() {
	return ScreensGlobal_DATA->lifes;
}

const u8** screensGlobal_getMapTiles() {
	return level01;
}

const u8** screensGlobal_getMapSprites() {
	return level01sprites;
}

