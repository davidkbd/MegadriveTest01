#include "math.h"

s32 math_pow(u8 times, s32 number) {
	s32 r = 1;	
	for (u8 i = 0; i < times; ++i) {
		r *= number;
	}
	return r;
}

