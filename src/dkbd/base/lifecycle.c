#include "lifecycle.h"
#include "lifecycle_private.h"

#include "event_timer_handler.h"

#include "../io/joy_handlers.h"

void lifecycle_resetUpdater() {
	lifecycle_update = lifecycle_default;
}

// ============================ PRIVATE ============================ //

void lifecycle_default() {
	eventTimerHandler_update();
}

void lifecycle_clearPlans() {
	VDP_clearPlan(PLAN_A, TRUE);
	VDP_clearPlan(PLAN_B, TRUE);
	VDP_clearPlan(PLAN_WINDOW, TRUE);
	VDP_clearTextArea(0, 0, 39, 27);
}

void lifecycle_changeScreen(void (*pInitialize)(), void (*pUpdate)()) {
	lifecycle_clearPlans();
	pInitialize();
	lifecycle_update = pUpdate;
}

void lifecycle_configureControls(
		void (*pOnKeyPressStartFunction)(u16),
		void (*pOnKeyPressAFunction)(u16),
		void (*pOnKeyPressBFunction)(u16),
		void (*pOnKeyPressCFunction)(u16),
		void (*pOnKeyPressXFunction)(u16),
		void (*pOnKeyPressYFunction)(u16),
		void (*pOnKeyPressZFunction)(u16),
		void (*pOnKeyPressUpFunction)(u16),
		void (*pOnKeyPressDownFunction)(u16),
		void (*pOnKeyPressLeftFunction)(u16),
		void (*pOnKeyPressRightFunction)(u16),
		void (*pOnKeyReleaseStartFunction)(u16),
		void (*pOnKeyReleaseAFunction)(u16),
		void (*pOnKeyReleaseBFunction)(u16),
		void (*pOnKeyReleaseCFunction)(u16),
		void (*pOnKeyReleaseXFunction)(u16),
		void (*pOnKeyReleaseYFunction)(u16),
		void (*pOnKeyReleaseZFunction)(u16),
		void (*pOnKeyReleaseUpFunction)(u16),
		void (*pOnKeyReleaseDownFunction)(u16),
		void (*pOnKeyReleaseLeftFunction)(u16),
		void (*pOnKeyReleaseRightFunction)(u16)
		) {
	onKeyPressStartFunction   = pOnKeyPressStartFunction;
	onKeyPressAFunction       = pOnKeyPressAFunction;
	onKeyPressBFunction       = pOnKeyPressBFunction;
	onKeyPressCFunction       = pOnKeyPressCFunction;
	onKeyPressXFunction       = pOnKeyPressXFunction;
	onKeyPressYFunction       = pOnKeyPressYFunction;
	onKeyPressZFunction       = pOnKeyPressZFunction;
	onKeyPressUpFunction      = pOnKeyPressUpFunction;
	onKeyPressDownFunction    = pOnKeyPressDownFunction;
	onKeyPressLeftFunction    = pOnKeyPressLeftFunction;
	onKeyPressRightFunction   = pOnKeyPressRightFunction;
	onKeyReleaseStartFunction = pOnKeyReleaseStartFunction;
	onKeyReleaseAFunction     = pOnKeyReleaseAFunction;
	onKeyReleaseBFunction     = pOnKeyReleaseBFunction;
	onKeyReleaseCFunction     = pOnKeyReleaseCFunction;
	onKeyReleaseXFunction     = pOnKeyReleaseXFunction;
	onKeyReleaseYFunction     = pOnKeyReleaseYFunction;
	onKeyReleaseZFunction     = pOnKeyReleaseZFunction;
	onKeyReleaseUpFunction    = pOnKeyReleaseUpFunction;
	onKeyReleaseDownFunction  = pOnKeyReleaseDownFunction;
	onKeyReleaseLeftFunction  = pOnKeyReleaseLeftFunction;
	onKeyReleaseRightFunction = pOnKeyReleaseRightFunction;
	JOY_setEventHandler( &disabledJoyHandler );
}
