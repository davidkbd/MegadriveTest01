#include <genesis.h>

// =========================== UI =========================== //

#define G_TILEINDEX_CHARSET 0x05A0
#define G_TILEINDEX_NUMBERS 0x05B0

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

#define G_TILEINDEX_HUD_ITEMS1   0x04b4
#define G_TILEINDEX_HUD_ITEMS2   0x04b6
#define G_TILEINDEX_HUD_ITEMS3   0x04b8
#define G_TILEINDEX_HUD_ITEMS4   0x04ba
#define G_TILEINDEX_HUD_ITEMS5   0x04bc
#define G_TILEINDEX_HUD_ITEMS6   0x04be
#define G_TILEINDEX_HUD_ITEMS1_B 0x04b5
#define G_TILEINDEX_HUD_ITEMS2_B 0x04b7
#define G_TILEINDEX_HUD_ITEMS3_B 0x04b9
#define G_TILEINDEX_HUD_ITEMS4_B 0x04bb
#define G_TILEINDEX_HUD_ITEMS5_B 0x04bd
#define G_TILEINDEX_HUD_ITEMS6_B 0x04bf

#define G_TILEINDEX_HUD_LIFES1   0x04c4
#define G_TILEINDEX_HUD_LIFES2   0x04c6
#define G_TILEINDEX_HUD_LIFES1_B 0x04c5
#define G_TILEINDEX_HUD_LIFES2_B 0x04c7

// =========================== SCENE  =========================== //

// Anterior al primer tile, de tal forma que G_TILEINDEX_MAP + (tile size) = G_TILEINDEX_FLOOR
#define G_TILEINDEX_MAP        0x001C
#define G_TILEINDEX_FLOOR      0x0020
#define G_TILEINDEX_FLOOR2     0x0060
#define G_TILEINDEX_BACKGROUND 0x00A0
#define G_TILEINDEX_WALL       0x0120
#define G_TILEINDEX_PITFALLS   0x0140
#define G_TILEINDEX_PLANB      0x0200

void screensGlobal_initialize();

void screensGlobal_finalize();

void screensGlobal_setCurrentStage(u8 p);

void screensGlobal_setScore(u16 p) ;

void screensGlobal_setLifes(u8 p);

u8 screensGlobal_getCurrentStage();

u16 screensGlobal_getScore();

u8 screensGlobal_getLifes();

const u8** screensGlobal_getMapTiles();

const u8** screensGlobal_getMapSprites();
