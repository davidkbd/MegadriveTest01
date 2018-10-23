#include "testingame.h"
#include "testingame_private.h"
#include "testingame_private_ia.h"

#include "../base/lifecycle.h"
#include "../base/hud.h"
#include "../base/event_timer_handler.h"
#include "../io/joy_handlers.h"
#include "../util/palette.h"
#include "../util/map.h"
#include "../maps/level01_b.h"
#include "../maps/level01.h"


#include "../../../res/sprite.h"
#include "../../../res/gfx.h"
#include "../base/viewport.h"

void testIngame_initializePlayer(s16 x, s16 y);

// ================ INIT ================ //

void testIngame_initUI() {
	//Esto posiciona el window abajo pero mejor vamos a hacer un hud con sprites
	//VDP_setWindowHPos(FALSE, 0);
	//VDP_setWindowVPos(TRUE, 25);

	VDP_setTextPalette(PAL3);
}

void testIngame_initMemory() {
	TestIngame_DATA = MEM_alloc(sizeof(struct TestIngame_ScreenData));
}

void testIngame_initData() {
	map_load(&level01_b, &level01);
	TestIngame_DATA->screenData.frameCount = 0;
	TestIngame_DATA->screenData.sceneAnimationFrame = 0;
	hud_reset();

	testIngame_initializePlayer(1800, 1400);
	viewport_reset(0, 0);

	// PROBANDO Sprites
	for (u8 i = 1; i < TestIngame_NUM_SPRITES; ++i) {
		TestIngame_Sprite *s = &(TestIngame_DATA->sprites[i]);
		s->sprite = 0;
		//s->alwaysOnTop = TRUE;
		s->spriteDef = &palmtree;
		s->position.x = 2400 + i * 200; // Puede que casque estando tan cerca
		s->position.y = 900 + i * 200; // Puede que casque estando tan cerca
		s->size.x = 160;
		s->size.y = 160;
		s->update = testIngame_onInanimatedUpdate;
	}
}

void testIngame_initSound() {
}

void testIngame_initPalete() {
	VDP_setPaletteColors(0, (u16*) palette_black, 64);

	palette_loadScreen(0);
	palette_loadHud(0);
	palette_loadEnemies(1);

	palette_write(PAL2, testingame_player.palette->data);
}

void testIngame_initBackgrounds() {
	VDP_loadTileData(ingame_subfloor_liquid_tile.tiles, G_TILEINDEX_SUBFLOOR, 8,                           FALSE);
	VDP_loadTileData(ingame_floor_tile.tiles,           G_TILEINDEX_FLOOR,    ingame_floor_tile.numTile,   FALSE);
	VDP_loadTileData(ingame_flowers_tile.tiles,         G_TILEINDEX_FLOWERS,  ingame_flowers_tile.numTile, FALSE);
	VDP_loadTileData(ingame_trees_tile.tiles,           G_TILEINDEX_TREES,    ingame_trees_tile.numTile, FALSE);
	VDP_loadTileData(ingame_wall_tile.tiles,            G_TILEINDEX_WALL,     ingame_wall_tile.numTile,  FALSE);
}

void testIngame_initSprites() {
	TestIngame_DATA->hudTimeSprite.sprite = SPR_addSprite(&hud_time, 5, 3, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
	SPR_setAlwaysOnTop(TestIngame_DATA->hudTimeSprite.sprite, TRUE);

	TestIngame_DATA->hudScoreSprite.sprite = SPR_addSprite(&hud_score, 5, 19, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
	SPR_setAlwaysOnTop(TestIngame_DATA->hudScoreSprite.sprite, TRUE);

	TestIngame_DATA->hudAnimalsSprite.sprite = SPR_addSprite(&hud_animals, 265, 202, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
	SPR_setAlwaysOnTop(TestIngame_DATA->hudAnimalsSprite.sprite, TRUE);

	TestIngame_DATA->sprites[0].sprite = SPR_addSprite(&testingame_player, 0, 0, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

	SPR_update();
}

// ================ FINALIZE ================ //

void testIngame_finalizeSound() {
}

void testIngame_finalizeGraphics() {
	SPR_releaseSprite(TestIngame_DATA->hudTimeSprite.sprite);
	SPR_releaseSprite(TestIngame_DATA->hudAnimalsSprite.sprite);
	SPR_releaseSprite(TestIngame_DATA->hudScoreSprite.sprite);
	
	for (u8 i=0; i<TestIngame_NUM_SPRITES; ++i) {
		SPR_releaseSprite(TestIngame_DATA->sprites[i].sprite);
	}
	VDP_clearTextArea(0, 0, 39, 27);
}

void testIngame_finalizeMemory() {
	MEM_free(TestIngame_DATA);
}

////////////////////////////////////////////////////////


void testIngame_initializePlayer(s16 x, s16 y) {
	TestIngame_DATA->playerSpritePTR = &(TestIngame_DATA->sprites[0]);
	TestIngame_Sprite *s = TestIngame_DATA->playerSpritePTR;
	s->spriteDef = &testingame_player;
	s->position.x = x;
	s->position.y = y;
	s->size.x = 400;
	s->size.y = 480;
	s->xCenter = 200;
	s->collider.pos1.x = -140;
	s->collider.pos1.y = -90;
	s->collider.pos2.x = 140;
	s->collider.pos2.y = -20;
	s->data = 0;
	s->update = testIngame_onPlayerUpdate;
}

