#include "numbers.h"

void numbers_toTimeMmss(numbers_callback callback, u16 timeInSeconds) {
	u8 seconds = timeInSeconds % 60;
	u8 minutes = timeInSeconds / 60;
	u8 numbers[4];
	numbers[0] = seconds % 10;
	numbers[1] = seconds / 10;
	numbers[2] = minutes % 10;
	numbers[3] = minutes / 10;
	callback(numbers, 4);
}

void numbers_toDigitBaseN(numbers_callback callback, u8 base, u16 number) {
	u16 resto = number;
	u8 buffer[24];
	u8 iBuffer = 0;
	while (resto > 0) {
		buffer[iBuffer] = resto % base;
		resto /= base;
		++iBuffer;
	}
	callback(buffer, iBuffer);
}

