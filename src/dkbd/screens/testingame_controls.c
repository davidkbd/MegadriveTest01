#include "testingame.h"
#include "testingame_private.h"

#include "../util/palette.h"
#include "../util/limits.h"

#define MAX_VEL_X 34
#define MAX_VEL_Y 17

void testIngame_pressingXAxis();
void testIngame_pressingYAxis();
void testIngame_notPressingXAxis();
void testIngame_notPressingYAxis();

void testIngame_onKeyPressStartFunction(u16 joy) {
	testIngame_beginExit();
}

void testIngame_onKeyPressAFunction(u16 joy) {
}

void testIngame_onKeyPressBFunction(u16 joy) {
}

void testIngame_onKeyPressCFunction(u16 joy) {
}

void testIngame_onKeyPressXFunction(u16 joy) {
}

void testIngame_onKeyPressYFunction(u16 joy) {
}

void testIngame_onKeyPressZFunction(u16 joy) {
}

void testIngame_onKeyPressUpFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data |= TestIngame_KEY_UP;
}

void testIngame_onKeyPressDownFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data |= TestIngame_KEY_DOWN;
}

void testIngame_onKeyPressLeftFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data |= TestIngame_KEY_LEFT;
}

void testIngame_onKeyPressRightFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data |= TestIngame_KEY_RIGHT;
}

void testIngame_onKeyReleaseStartFunction(u16 joy) {
}

void testIngame_onKeyReleaseAFunction(u16 joy) {
}

void testIngame_onKeyReleaseBFunction(u16 joy) {
}

void testIngame_onKeyReleaseCFunction(u16 joy) {
}

void testIngame_onKeyReleaseXFunction(u16 joy) {
}

void testIngame_onKeyReleaseYFunction(u16 joy) {
}

void testIngame_onKeyReleaseZFunction(u16 joy) {
}

void testIngame_onKeyReleaseUpFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data &= TestIngame_NOKEY_UP;
}

void testIngame_onKeyReleaseDownFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data &= TestIngame_NOKEY_DOWN;
}

void testIngame_onKeyReleaseLeftFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data &= TestIngame_NOKEY_LEFT;
}

void testIngame_onKeyReleaseRightFunction(u16 joy) {
	TestIngame_DATA->playerSpritePTR->data &= TestIngame_NOKEY_RIGHT;
}

void testIngame_updateControls() {
	testIngame_pressingXAxis();
	testIngame_notPressingXAxis();
	testIngame_pressingYAxis();
	testIngame_notPressingYAxis();
}

u8 testIngame_isPressingUp() {
	return TestIngame_KEY_UP & TestIngame_DATA->playerSpritePTR->data;
}

u8 testIngame_isPressingLeft() {
	return TestIngame_KEY_LEFT & TestIngame_DATA->playerSpritePTR->data;
}

u8 testIngame_isPressingRight() {
	return TestIngame_KEY_RIGHT & TestIngame_DATA->playerSpritePTR->data;
}

u8 testIngame_isPressingDown() {
	return TestIngame_KEY_DOWN & TestIngame_DATA->playerSpritePTR->data;
}

void testIngame_pressingXAxis() {
	if (testIngame_isPressingLeft() && TestIngame_DATA->playerData.xSpeed > -MAX_VEL_X) {
		TestIngame_DATA->playerData.xSpeed -= 2;
	}
	if (testIngame_isPressingRight() && TestIngame_DATA->playerData.xSpeed < MAX_VEL_X) {
		TestIngame_DATA->playerData.xSpeed += 2;
	}
}

void testIngame_pressingYAxis() {
	if (testIngame_isPressingUp() && TestIngame_DATA->playerData.ySpeed > -MAX_VEL_Y) {
		TestIngame_DATA->playerData.ySpeed -= 2;
	}
	if (testIngame_isPressingDown() && TestIngame_DATA->playerData.ySpeed < MAX_VEL_Y) {
		TestIngame_DATA->playerData.ySpeed += 2;
	}
}

void testIngame_notPressingXAxis() {
	if (!testIngame_isPressingLeft() && !testIngame_isPressingRight()) {
		if (TestIngame_DATA->playerData.xSpeed > 0) {
			TestIngame_DATA->playerData.xSpeed /= 2;
			if (TestIngame_DATA->playerData.xSpeed < 1) {
				TestIngame_DATA->playerData.xSpeed = 0;
			}
		} else if (TestIngame_DATA->playerData.xSpeed < 0) {
			TestIngame_DATA->playerData.xSpeed /= 2;
			if (TestIngame_DATA->playerData.xSpeed > -1) {
				TestIngame_DATA->playerData.xSpeed = 0;
			}
		}
	}
}

void testIngame_notPressingYAxis() {
	if (!testIngame_isPressingUp() && !testIngame_isPressingDown()) {
		if (TestIngame_DATA->playerData.ySpeed > 0) {
			TestIngame_DATA->playerData.ySpeed /= 2;
			if (TestIngame_DATA->playerData.ySpeed < 1) {
				TestIngame_DATA->playerData.ySpeed = 0;
			}
		} else if (TestIngame_DATA->playerData.ySpeed < 0) {
			TestIngame_DATA->playerData.ySpeed /= 2;
			if (TestIngame_DATA->playerData.ySpeed > -1) {
				TestIngame_DATA->playerData.ySpeed = 0;
			}
		}
	}
}
