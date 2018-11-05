#include "container4u16.h"

u16 container4U16_getSlotValue(u16 data, u8 slot) {
	switch (slot) {
		case 1:
			return (data & 0b111000000000) >> 9;
		case 2:
			return (data & 0b000111000000) >> 6;
		case 3:
			return (data & 0b000000111000) >> 3;
		case 4:
			return data & 0b000000000111;
	}
	return -1;
}

void container4U16_setSlotValue(u16 *data, u8 slot, u16 value) {
	if (value > 7 || slot > 4) {
		return;
	}
	u16 mask = value;
	switch (slot) {
		case 1:
			mask = mask << 9;
			*data = *data & 0b1111000111111111;
			break;
		case 2:
			mask = mask << 6;
			*data = *data & 0b1111111000111111;
			break;
		case 3:
			mask = mask << 3;
			*data = *data & 0b1111111111000111;
			break;
		case 4:
			*data = *data & 0b1111111111111000;
			break;
	}
	*data = *data | mask;
}

u8 container4U16_getSwitchState(u16 data, u8 slot) {
	switch (slot) {
		case 1:
			return (data & 0b100000000000000) >> 14;
		case 2:
			return (data & 0b010000000000000) >> 13;
		case 3:
			return (data & 0b001000000000000) >> 12;
		case 4:
			return (data & 0b000100000000000) >> 11;
	}
	return -1;
}

void container4U16_enableSwitch(u16 *data, u8 slot) {
	switch (slot) {
		case 1:
			*data = *data | 0b100000000000000;
			break;
		case 2:
			*data = *data | 0b010000000000000;
			break;
		case 3:
			*data = *data | 0b001000000000000;
			break;
		case 4:
			*data = *data | 0b000100000000000;
			break;
	}
}

void container4U16_disableSwitch(u16 *data, u8 slot) {
	switch (slot) {
		case 1:
			*data = *data & 0b011111111111111;
			break;
		case 2:
			*data = *data & 0b101111111111111;
			break;
		case 3:
			*data = *data & 0b110111111111111;
			break;
		case 4:
			*data = *data & 0b111011111111111;
			break;
	}
}

