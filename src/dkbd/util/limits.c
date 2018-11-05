#include "limits.h"

s8 limits_s8(s8 number, s8 min, s8 max) {
	if (number >= max) {
		return max - 1;
	}
	if (number < min) {
		return min;
	}
	return number;
}

s16 limits_s16(s16 number, s16 min, s16 max) {
	if (number >= max) {
		return max - 1;
	}
	if (number < min) {
		return min;
	}
	return number;
}

s32 limits_s32(s32 number, s32 min, s32 max) {
	if (number >= max) {
		return max - 1;
	}
	if (number < min) {
		return min;
	}
	return number;
}

s8 limits_incr_s8(s8 number, s8 incr, s8 min, s8 max) {
	return limits_s8(number + incr, min, max);
}

s16 limits_incr_s16(s16 number, s16 incr, s16 min, s16 max) {
	return limits_s16(number + incr, min, max);
}

s32 limits_incr_s32(s32 number, s32 incr, s32 min, s32 max) {
	return limits_s32(number + incr, min, max);
}

s8 limits_cycle_s8(s8 number, s8 incr, s8 min, s8 max) {
	s8 r = number + incr;
	s8 diff = min - max;
	while (r >= max) {
		r += diff;
	}
	while (r < min) {
		r = r - diff;
	}
	return r;
}

s16 limits_cycle_s16(s16 number, s16 incr, s16 min, s16 max) {
	s16 r = number + incr;
	s16 diff = min - max;
	while (r >= max) {
		r += diff;
	}
	while (r < min) {
		r = r - diff;
	}
	return r;
}

s32 limits_cycle_s32(s32 number, s32 incr, s32 min, s32 max) {
	s32 r = number + incr;
	s32 diff = min - max;
	while (r >= max) {
		r += diff;
	}
	while (r < min) {
		r = r - diff;
	}
	return r;
}
