#include "ingame_platforms.h"
#include "ingame_platforms_private.h"

#include "../base/event_timer_handler.h"

#include "../util/palette.h"
#include "../util/limits.h"

void ingamePlatforms_pressingXAxis();
void ingamePlatforms_notPressingXAxis();
void ingamePlatforms_releaseAction();
void ingamePlatforms_controlViewport();

void ingamePlatforms_onKeyPressStartFunction(u16 joy) {
	ingamePlatforms_beginExit();
}

void ingamePlatforms_onKeyPressAFunction(u16 joy) {
	if (!ingamePlatforms_isPressingAction()) {
		IngamePlatforms_DATA->playerSpritePTR->data |= IngamePlatforms_KEY_ACTION;
		eventTimerHandler_reset();
		eventTimerHandler_addSlot(5, ingamePlatforms_releaseAction);
		eventTimerHandler_enable();
	}
}

void ingamePlatforms_onKeyPressBFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data |= IngamePlatforms_KEY_JUMP;
}

void ingamePlatforms_onKeyPressCFunction(u16 joy) {
	if (!ingamePlatforms_isPressingAction()) {
		IngamePlatforms_DATA->playerSpritePTR->data |= IngamePlatforms_KEY_ACTION;
		eventTimerHandler_reset();
		eventTimerHandler_addSlot(5, ingamePlatforms_releaseAction);
		eventTimerHandler_enable();
	}
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
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_ACTION;
}

void ingamePlatforms_onKeyReleaseBFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_JUMP;
}

void ingamePlatforms_onKeyReleaseCFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_ACTION;
}

void ingamePlatforms_onKeyReleaseXFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseYFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseZFunction(u16 joy) {
}

void ingamePlatforms_onKeyReleaseUpFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_UP;
}

void ingamePlatforms_onKeyReleaseDownFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_DOWN;
}

void ingamePlatforms_onKeyReleaseLeftFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_LEFT;
}

void ingamePlatforms_onKeyReleaseRightFunction(u16 joy) {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_RIGHT;
}

void ingamePlatforms_updateControls() {
	ingamePlatforms_pressingXAxis();
	ingamePlatforms_notPressingXAxis();

	ingamePlatforms_controlViewport();

	IngameSprite *player = IngamePlatforms_DATA->playerSpritePTR;
	if (ingamePlatforms_isPressingJump() && player->onFloor) {
		player->onFloor = 0;
		player->speed.y = INGAME_PLATFORMS_JUMP_FORCE;
		player->data &= IngamePlatforms_DISABLEKEY_JUMP;
	}
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

u8 ingamePlatforms_isPressingJump() {
	return IngamePlatforms_KEY_JUMP & IngamePlatforms_DATA->playerSpritePTR->data;
}

u8 ingamePlatforms_isPressingAction() {
	return IngamePlatforms_KEY_ACTION & IngamePlatforms_DATA->playerSpritePTR->data;
}

void ingamePlatforms_pressingXAxis() {
	Vector2 *speed = &IngamePlatforms_DATA->playerSpritePTR->speed;
	if (ingamePlatforms_isPressingLeft() && speed->x > -INGAME_PLATFORMS_MAX_X_SPEED) {
		speed->x -= 2;
	}
	if (ingamePlatforms_isPressingRight() && speed->x < INGAME_PLATFORMS_MAX_X_SPEED) {
		speed->x += 2;
	}
}

void ingamePlatforms_notPressingXAxis() {
	if (!ingamePlatforms_isPressingLeft() && !ingamePlatforms_isPressingRight()) {
		Vector2 *speed = &IngamePlatforms_DATA->playerSpritePTR->speed;
		if (speed->x > 0) {
			speed->x /= 2;
			if (speed->x < 1) {
				speed->x = 0;
			}
		} else if (speed->x < 0) {
			speed->x /= 2;
			if (speed->x > -1) {
				speed->x = 0;
			}
		}
	}
}

void ingamePlatforms_releaseAction() {
	IngamePlatforms_DATA->playerSpritePTR->data &= IngamePlatforms_DISABLEKEY_ACTION;
}

void ingamePlatforms_controlViewport() {
	IngameSprite *s = IngamePlatforms_DATA->playerSpritePTR;
	Vector2 *viewportOffset = &(IngamePlatforms_DATA->screenData.viewportOffset);
	if (ingamePlatforms_isPressingRight() && abs(s->speed.x) > 10) {
		if (viewportOffset->x > 1600) {
			viewportOffset->x = 1600;
		}
		if (viewportOffset->x > 900) {
			viewportOffset->x -= 20;
		}
	} else if (ingamePlatforms_isPressingLeft()) {
		if (viewportOffset->x < 1600) {
				viewportOffset->x = 1600;
			}
		if (viewportOffset->x < 2300) {
			viewportOffset->x += 20;
		}
	} else {
		if (viewportOffset->x > 1600) {
			viewportOffset->x -= 20;
		}
		if (viewportOffset->x < 1600) {
			viewportOffset->x += 20;
		}
	}
	if (s->onFloor && ingamePlatforms_isPressingDown()) {
		viewportOffset->y = 500;
	} else if (s->onFloor && ingamePlatforms_isPressingUp()) {
		viewportOffset->y = 2000;
	} else {
		//1200 seria el centro
		viewportOffset->y = 1600;
	}
}
