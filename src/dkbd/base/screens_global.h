#include <genesis.h>

#include "../util/vector2.h"
#include "../util/map.h"
#include "../maps/level01.h"
#include "../maps/level01_sprites.h"

#ifndef SCREENS_GLOBAL_H_
#define SCREENS_GLOBAL_H_

struct ScreensGlobal_Screen_st {
	const u8 **map;
	const u8 **sprites;
	const char name[10];
	const Vector2 initialPosition;
};
typedef struct ScreensGlobal_Screen_st ScreensGlobal_Screen;

static const ScreensGlobal_Screen ScreensGlobal_SCREENS[4] = {
		{ .map = level01, .sprites = level01sprites, .name = "green hill", .initialPosition = {3600, 1000}},
		{ .map = level01, .sprites = level01sprites, .name = "green hill", .initialPosition = {600, 1000}},
		{ .map = level01, .sprites = level01sprites, .name = "green hill", .initialPosition = {1200, 20000}}
};

#endif


// =========================== UI =========================== //

#define G_TILEINDEX_CHARSET 0x05A0
#define G_TILEINDEX_NUMBERS 0x05B0
#define G_TILEINDEX_LETTERS 0x05B0

// =========================== HUD =========================== //

#define G_TILEINDEX_HUD_TIME1    0x04a0
#define G_TILEINDEX_HUD_TIME2    0x04a2
#define G_TILEINDEX_HUD_TIME3    0x04a6
#define G_TILEINDEX_HUD_TIME4    0x04a8
#define G_TILEINDEX_HUD_TIME1_B  0x04a1
#define G_TILEINDEX_HUD_TIME2_B  0x04a3
#define G_TILEINDEX_HUD_TIME3_B  0x04a7
#define G_TILEINDEX_HUD_TIME4_B  0x04a9

#define G_TILEINDEX_HUD_SCORE1   0x04aa
#define G_TILEINDEX_HUD_SCORE2   0x04ac
#define G_TILEINDEX_HUD_SCORE3   0x04ae
#define G_TILEINDEX_HUD_SCORE4   0x04b0
#define G_TILEINDEX_HUD_SCORE5   0x04b2
#define G_TILEINDEX_HUD_SCORE1_B 0x04ab
#define G_TILEINDEX_HUD_SCORE2_B 0x04ad
#define G_TILEINDEX_HUD_SCORE3_B 0x04af
#define G_TILEINDEX_HUD_SCORE4_B 0x04b1
#define G_TILEINDEX_HUD_SCORE5_B 0x04b3

#define G_TILEINDEX_HUD_LIFES    0x04c0
#define G_TILEINDEX_HUD_LIFES1   0x04c4
#define G_TILEINDEX_HUD_LIFES2   0x04c6
#define G_TILEINDEX_HUD_LIFES1_B 0x04c5
#define G_TILEINDEX_HUD_LIFES2_B 0x04c7


#define G_TILEINDEX_PLAYER      0x04c8

#define G_TILEINDEX_SPRITES     0x04a4

// =========================== SCENE  =========================== //

// Anterior al primer tile, de tal forma que G_TILEINDEX_MAP + (tile size) = G_TILEINDEX_FLOOR
#define G_TILEINDEX_MAP         0x001C
#define G_TILEINDEX_FLOOR       0x0020
#define G_TILEINDEX_FLOOR2      0x0060
#define G_TILEINDEX_WALL        0x00A0
#define G_TILEINDEX_BACKGROUND  0x00E0
#define G_TILEINDEX_BACKGROUND2 0x0120
#define G_TILEINDEX_BACKGROUND3 0x0160
#define G_TILEINDEX_BACKGROUND4 0x01A0
#define G_TILEINDEX_BACKGROUND5 0x01E0
#define G_TILEINDEX_BACKGROUND6 0x0220

#define G_TILEINDEX_PAUSASCREEN 0x0260
#define G_TILEINDEX_PLANB       0x0320


#define G_SPR_POSITION_HUD_TIME_X 5
#define G_SPR_POSITION_HUD_TIME_Y 3
#define G_SPR_POSITION_HUD_SCORE_X 5
#define G_SPR_POSITION_HUD_SCORE_Y 19
#define G_SPR_POSITION_HUD_LIFES_X 5
#define G_SPR_POSITION_HUD_LIFES_Y 202

void screensGlobal_initialize();

void screensGlobal_finalize();

void screensGlobal_setCurrentStage(u8 p);

void screensGlobal_setScore(u16 p) ;

void screensGlobal_setLifes(u8 p);

u8 screensGlobal_getCurrentStage();

u16 screensGlobal_getScore();

u8 screensGlobal_getLifes();
