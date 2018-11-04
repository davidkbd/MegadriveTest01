#include <genesis.h>

struct TitleScreen_DATA_st {
	Sprite* letters[10];
	u8 positions[10];
	u16 timer;
} * TitleScreen_DATA;

void titleScreen_initialize(const char *text);

void titleScreen_update();

