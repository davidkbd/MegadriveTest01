#include <genesis.h>

typedef void (*numbers_callback)(u8 *digits, u8 length);


void numbers_toTimeMmss(numbers_callback callback, u16 timeInSeconds);
void numbers_toDigitBaseN(numbers_callback callback, u8 base, u16 number);

