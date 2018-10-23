#include "string.h"

#include "math.h"

u32 string_strToU32(u8 *str) {
	u32 r = 0;
	u8 len = string_length(str);
	u8 i = len;
	for (u8 pos = 0; pos < len; ++pos) {
		--i;
		u8 digit = str[i] - '0';
		r += digit * math_pow(pos, 10);
	}
	return r;
}

u8 string_length(u8 *str) {
	u8 i = 0;
	while (str[i] != NULL) {
		++i;
	}
	return i;
}

