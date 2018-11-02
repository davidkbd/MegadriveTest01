#include <genesis.h>

u16 palette_rgb(u8 r, u8 g, u8 b);
void palette_write(u8 pal, u16* data);
void palette_putColor(u8 pal, u16 colorIndex, u16 color);
void palette_apply();
void palette_fadeIn();

void palette_loadScreen(u8 screenId);
void palette_loadHud(u8 status);
void palette_loadEnemies(u8 type);
