#include "ingame_platforms.h"
#include "ingame_platforms_private.h"

#include "../util/palette.h"
#include "../util/limits.h"

#define MAX_VEL_X 34
#define MAX_VEL_Y 17

void ingamePlatforms_pressingXAxis();
void ingamePlatforms_pressingYAxis();
void ingamePlatforms_notPressingXAxis();
void ingamePlatforms_notPressingYAxis();

void ingamePlatforms_onKeyPressStartFunction(u16 joy) {
	ingamePlatforms_beginExit();
}

void ingamePlatforms_onKeyPressAFunction(u16 joy) {
}

void ingamePlatforms_onKeyPressBFunction(u16 joy) {
}

void ingamePlatforms_onKeyPressCFunction(u16 joy) {
}

void ingamePlatforms_onKeyPressXFunction(u16 joy) {
}

void ingamePlatforms_onKeyPressYFunction(u16 joy) {
}

void ingamePlatforms_onKeyPressZFunction(u16 joy) {
}

void ingamePlatforms_onKeyPressUpFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data |= IngamePlatforms_KEY_UP;
}

void ingamePlatforms_onKeyPressDownFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data |= IngamePlatforms_KEY_DOWN;
}

void ingamePlatforms_onKeyPressLeftFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data |= IngamePlatforms_KEY_LEFT;
}

void ingamePlatforms_onKeyPressRightFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data |= IngamePlatforms_KEY_RIGHT;
}

void ingamePlatforms_onKeyReleaseStartFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseAFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseBFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseCFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseXFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseYFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseZFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseUpFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_NOKEY_UP;
}

void ingamePlatforms_onKeyReleaseDownFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_NOKEY_DOWN;
}

void ingamePlatforms_onKeyReleaseLeftFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_NOKEY_LEFT;
}

void ingamePlatforms_onKeyReleaseRightFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_NOKEY_RIGHT;
}

void ingamePlatforms_updateControls() {
	ingamePlatforms_pressingXAxis();
	ingamePlatforms_notPressingXAxis();
	ingamePlatforms_pressingYAxis();
	ingamePlatforms_notPressingYAxis();
}

u8 ingamePlatforms_isPressingUp() {
	return IngamePlatforms_KEY_UP & IngamePlatforms_DATA->playerSpritePTR->data;
}

u8 ingamePlatforms_isPressingLeft() {
	return IngamePlatforms_KEY_LEFT & IngamePlatforms_DATA->playerSpritePTR->data;
}

u8 ingamePlatforms_isPressingRight() {
	return IngamePlatforms_KEY_RIGHT & IngamePlatforms_DATA->playerSpritePTR->data;
}

u8 ingamePlatforms_isPressingDown() {
	return IngamePlatforms_KEY_DOWN & IngamePlatforms_DATA->playerSpritePTR->data;
}

void ingamePlatforms_pressingXAxis() {
	if (ingamePlatforms_isPressingLeft() && IngamePlatforms_DATA->playerData.xSpeed > -MAX_VEL_X) {
		IngamePlatforms_DATA->playerData.xSpeed -= 2;
	}
	if (ingamePlatforms_isPressingRight() && IngamePlatforms_DATA->playerData.xSpeed < MAX_VEL_X) {
		IngamePlatforms_DATA->playerData.xSpeed += 2;
	}
}

void ingamePlatforms_pressingYAxis() {
	if (ingamePlatforms_isPressingUp() && IngamePlatforms_DATA->playerData.ySpeed > -MAX_VEL_Y) {
		IngamePlatforms_DATA->playerData.ySpeed -= 2;
	}
	if (ingamePlatforms_isPressingDown() && IngamePlatforms_DATA->playerData.ySpeed < MAX_VEL_Y) {
		IngamePlatforms_DATA->playerData.ySpeed += 2;
	}
}

void ingamePlatforms_notPressingXAxis() {
	if (!ingamePlatforms_isPressingLeft() && !ingamePlatforms_isPressingRight()) {
		if (IngamePlatforms_DATA->playerData.xSpeed > 0) {
			IngamePlatforms_DATA->playerData.xSpeed /= 2;
			if (IngamePlatforms_DATA->playerData.xSpeed < 1) {
				IngamePlatforms_DATA->playerData.xSpeed = 0;
			}
		} else if (IngamePlatforms_DATA->playerData.xSpeed < 0) {
			IngamePlatforms_DATA->playerData.xSpeed /= 2;
			if (IngamePlatforms_DATA->playerData.xSpeed > -1) {
				IngamePlatforms_DATA->playerData.xSpeed = 0;
			}
		}
	}
}

void ingamePlatforms_notPressingYAxis() {
	if (!ingamePlatforms_isPressingUp() && !ingamePlatforms_isPressingDown()) {
		if (IngamePlatforms_DATA->playerData.ySpeed > 0) {
			IngamePlatforms_DATA->playerData.ySpeed /= 2;
			if (IngamePlatforms_DATA->playerData.ySpeed < 1) {
				IngamePlatforms_DATA->playerData.ySpeed = 0;
			}
		} else if (IngamePlatforms_DATA->playerData.ySpeed < 0) {
			IngamePlatforms_DATA->playerData.ySpeed /= 2;
			if (IngamePlatforms_DATA->playerData.ySpeed > -1) {
				IngamePlatforms_DATA->playerData.ySpeed = 0;
			}
		}
	}
}
