#include "event_timer_handler.h"
#include "event_timer_handler_private.h"

void eventTimerHandler_reset() {
	EventTimerHandler_DATA.timer = 0;
	EventTimerHandler_DATA.slot_position = 0;
	EventTimerHandler_DATA.numSlots = 0;
	eventTimerHandler_disable();
}

void eventTimerHandler_addSlot(const u16 time, void (*callback)()) {
	EventTimerHandler_DATA.slots[EventTimerHandler_DATA.numSlots].time = time;
	EventTimerHandler_DATA.slots[EventTimerHandler_DATA.numSlots].callback = callback;
	if (EventTimerHandler_DATA.numSlots < EVENT_TIMER_HANDLER_PRIVATE_MAX_SLOTS) {
		++EventTimerHandler_DATA.numSlots;
	}
}

void eventTimerHandler_enable() {
	eventTimerHandler_update = eventTimerHandler_execute;
}

void eventTimerHandler_disable() {
	eventTimerHandler_update = eventTimerHandler_doNothing;
}

u8 eventTimerHandler_isEnabled() {
	return eventTimerHandler_update == eventTimerHandler_execute;
}

// ========================== //

void eventTimerHandler_execute() {
	if (EventTimerHandler_DATA.slot_position < EventTimerHandler_DATA.numSlots) {
		const EventTimerHandler_Slot *slot = &EventTimerHandler_DATA.slots[EventTimerHandler_DATA.slot_position];
		if (EventTimerHandler_DATA.timer >= slot->time) {
			++EventTimerHandler_DATA.slot_position;
			slot->callback();
		}
		++EventTimerHandler_DATA.timer;
	} else {
		eventTimerHandler_disable();
	}
}

void eventTimerHandler_doNothing() {
	// DO NOTHING...
}
