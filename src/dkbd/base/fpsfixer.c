#include "fpsfixer.h"

void fpsfixer_fixTo(u32 initialFrameTimeMillis, u8 millisPerFrame);

void fpsfixer_fixTo30FPS(u32 initialFrameTimeMillis) {
	fpsfixer_fixTo(initialFrameTimeMillis, 33);
}

void fpsfixer_fixTo40FPS(u32 initialFrameTimeMillis) {
	fpsfixer_fixTo(initialFrameTimeMillis, 10);
}

void fpsfixer_fixTo(u32 initialFrameTimeMillis, u8 millisPerFrame) {
	u32 transcurred = getTimeAsFix32(FALSE) - initialFrameTimeMillis;
	if (transcurred < millisPerFrame) {
		waitMs(millisPerFrame - transcurred);
	}
}
