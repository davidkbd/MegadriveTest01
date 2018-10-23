#include "configuration.h"

struct Configuration_DATA_st {
	u8 musicEnabled;
	u8 sfxEnabled;
	u8 difficulty;
	u8 buttonsMode;
} Configuration_DATA;

void configuration_initialize() {
	Configuration_DATA.musicEnabled = TRUE;
	Configuration_DATA.sfxEnabled = TRUE;
	Configuration_DATA.difficulty = 0;
	Configuration_DATA.buttonsMode = 0;
}

u8 configuration_isMusicEnabled() {
	return Configuration_DATA.musicEnabled;
}

void configuration_setMusicEnabled(u8 p) {
	Configuration_DATA.musicEnabled = p;
}

u8 configuration_isSfxEnabled() {
	return Configuration_DATA.sfxEnabled;
}

void configuration_setSfxEnabled(u8 p) {
	Configuration_DATA.sfxEnabled = p;
}

u8 configuration_getDifficulty() {
	return Configuration_DATA.difficulty;
}

void configuration_setDifficulty(u8 p) {
	Configuration_DATA.difficulty = p;
}

u8 configuration_getButtonsMode() {
	return Configuration_DATA.buttonsMode;
}

void configuration_setButtonsMode(u8 p) {
	Configuration_DATA.buttonsMode = p;
}
