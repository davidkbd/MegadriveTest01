#include "repeats.h"

u8 repeats_each(u32 time, u32 active, u32 all);

u8 repeats_delayed(u32 time, u32 firstDelay, u32 secondDelay, repeats_mode mode) {
	u32 allFirstDelays = firstDelay + secondDelay;
	if (time <= allFirstDelays) {
		if (time == firstDelay || time == allFirstDelays) {
			return TRUE;
		}
		return FALSE;
	} else {
		return mode(time - allFirstDelays);
	}
}

u8 repeats_delayed_combine(u32 time, u32 firstDelay, u32 secondDelay, repeats_mode mode1, repeats_mode mode2) {
	u32 allFirstDelays = firstDelay + secondDelay;
	if (time <= allFirstDelays) {
		if (time == firstDelay || time == allFirstDelays) {
			return TRUE;
		}
		return FALSE;
	} else {
		u32 t = time - allFirstDelays;
		return mode1(t) || mode2(t);
	}
}

u8 repeats_delayed_exclude(u32 time, u32 firstDelay, u32 secondDelay, repeats_mode mode1, repeats_mode mode2) {
	u32 allFirstDelays = firstDelay + secondDelay;
	if (time <= allFirstDelays) {
		if (time == firstDelay || time == allFirstDelays) {
			return TRUE;
		}
		return FALSE;
	} else {
		u32 t = time - allFirstDelays;
		return mode1(t) && mode2(t);
	}
}

u8 repeats_all_mode(u32 time) {
	return TRUE;
}

u8 repeats_1_each_2_mode(u32 time) {
	return (time % 2) == 0;
}

u8 repeats_1_each_3_mode(u32 time) {
	return (time % 3) == 0;
}

u8 repeats_1_each_4_mode(u32 time) {
	return (time % 4) == 0;
}

u8 repeats_1_each_5_mode(u32 time) {
	return (time % 5) == 0;
}

u8 repeats_2_each_3_mode(u32 time) {
	return repeats_each(time, 2, 3);
}

u8 repeats_2_each_4_mode(u32 time) {
	return repeats_each(time, 2, 4);
}

u8 repeats_2_each_5_mode(u32 time) {
	return repeats_each(time, 2, 5);
}

u8 repeats_3_each_4_mode(u32 time) {
	return repeats_each(time, 3, 4);
}

u8 repeats_3_each_5_mode(u32 time) {
	return repeats_each(time, 3, 5);
}

u8 repeats_4_each_5_mode(u32 time) {
	return repeats_each(time, 4, 5);
}

u8 repeats_1_each_10_mode(u32 time) {
	return repeats_each(time, 1, 10);
}

u8 repeats_3_each_10_mode(u32 time) {
	return repeats_each(time, 3, 10);
}

u8 repeats_7_each_10_mode(u32 time) {
	return repeats_each(time, 7, 10);
}

u8 repeats_1_each_20_mode(u32 time) {
	return repeats_each(time, 1, 20);
}

u8 repeats_1_each_30_mode(u32 time) {
	return repeats_each(time, 1, 30);
}

u8 repeats_1_each_40_mode(u32 time) {
	return repeats_each(time, 1, 40);
}

u8 repeats_1_each_50_mode(u32 time) {
	return repeats_each(time, 1, 50);
}

// -------------------------------------------------------- //

u8 repeats_each(u32 time, u32 active, u32 all) {
	for (int i=0; i<active; ++i) {
		if (((time + i) % all) == 0) {
			return TRUE;
		}
	}
	return FALSE;
}

