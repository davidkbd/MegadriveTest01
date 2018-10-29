#include "ingame_platforms.h"
#include "ingame_platforms_private.h"
#include "ingame_platforms_private_ia.h"

#include "../base/lifecycle.h"
#include "../base/hud.h"
#include "../base/event_timer_handler.h"
#include "../io/joy_handlers.h"
#include "../util/palette.h"
#include "../util/map.h"
#include "../maps/level01.h"


#include "../../../res/sprite.h"
#include "../../../res/gfx.h"
#include "../base/viewport.h"

void ingamePlatforms_initializePlayer(s16 x, s16 y);

// ================ INIT ================ //

void ingamePlatforms_initUI() {
	//Esto posiciona el window abajo pero mejor vamos a hacer un hud con sprites
	//VDP_setWindowHPos(FALSE, 0);
	//VDP_setWindowVPos(TRUE, 25);

	VDP_setTextPalette(PAL3);
}

void ingamePlatforms_initMemory() {
	IngamePlatforms_DATA = MEM_alloc(sizeof(struct IngamePlatforms_ScreenData));
}

void ingamePlatforms_initData() {
	map_load(&level01);
	IngamePlatforms_DATA->screenData.frameCount = 0;
	IngamePlatforms_DATA->screenData.sceneAnimationFrame = 0;
	IngamePlatforms_DATA->gravity = 9;
	hud_reset();

	ingamePlatforms_initializePlayer(1200, 300);
	viewport_reset(0, 0);

	// PROBANDO Sprites
	for (u8 i = 1; i < IngamePlatforms_NUM_SPRITES; ++i) {
		IngamePlatforms_Sprite *s = &(IngamePlatforms_DATA->sprites[i]);
		s->sprite = 0;
		//s->alwaysOnTop = TRUE;
		s->spriteDef = &palmtree;
		s->position.x = 2400 + i * 200; // Puede que casque estando tan cerca
		s->position.y = 900 + i * 200; // Puede que casque estando tan cerca
		s->size.x = 160;
		s->size.y = 160;
		s->update = ingamePlatforms_onInanimatedUpdate;
	}
}

void ingamePlatforms_initSound() {
}

void ingamePlatforms_initPalete() {
	VDP_setPaletteColors(0, (u16*) palette_black, 64);

	palette_loadScreen(0);
	palette_loadHud(0);
	palette_loadEnemies(1);

	palette_write(PAL2, testingame_player.palette->data);
}

void ingamePlatforms_initBackgrounds() {
	VDP_loadTileData(ingame_floor_tile.tiles,      G_TILEINDEX_FLOOR,        ingame_floor_tile.numTile,   FALSE);
	VDP_loadTileData(ingame_floor2_tile.tiles,     G_TILEINDEX_FLOOR2,       ingame_floor2_tile.numTile,   FALSE);
	VDP_loadTileData(ingame_background_tile.tiles, G_TILEINDEX_BACKGROUND,   ingame_background_tile.numTile,  FALSE);

	VDP_loadTileData(ingame_wall_tile.tiles,       G_TILEINDEX_WALL,   ingame_background_tile.numTile,  FALSE);


	VDP_drawImageEx(PLAN_B, &planb_level01, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_TILEINDEX_PLANB), 0, 0, TRUE, FALSE);
}

void ingamePlatforms_initSprites() {
	IngamePlatforms_DATA->hudTimeSprite.sprite = SPR_addSprite(&hud_time, 5, 3, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
	SPR_setAlwaysOnTop(IngamePlatforms_DATA->hudTimeSprite.sprite, TRUE);

	IngamePlatforms_DATA->hudScoreSprite.sprite = SPR_addSprite(&hud_score, 5, 19, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
	SPR_setAlwaysOnTop(IngamePlatforms_DATA->hudScoreSprite.sprite, TRUE);

	IngamePlatforms_DATA->hudAnimalsSprite.sprite = SPR_addSprite(&hud_animals, 265, 202, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
	SPR_setAlwaysOnTop(IngamePlatforms_DATA->hudAnimalsSprite.sprite, TRUE);

	IngamePlatforms_DATA->sprites[0].sprite = SPR_addSprite(&testingame_player, 0, 0, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

	SPR_update();
}

// ================ FINALIZE ================ //

void ingamePlatforms_finalizeSound() {
}

void ingamePlatforms_finalizeGraphics() {
	SPR_releaseSprite(IngamePlatforms_DATA->hudTimeSprite.sprite);
	SPR_releaseSprite(IngamePlatforms_DATA->hudAnimalsSprite.sprite);
	SPR_releaseSprite(IngamePlatforms_DATA->hudScoreSprite.sprite);
	
	for (u8 i=0; i < IngamePlatforms_NUM_SPRITES; ++i) {
		SPR_releaseSprite(IngamePlatforms_DATA->sprites[i].sprite);
	}
	VDP_clearTextArea(0, 0, 39, 27);
}

void ingamePlatforms_finalizeMemory() {
	MEM_free(IngamePlatforms_DATA);
}

////////////////////////////////////////////////////////


void ingamePlatforms_initializePlayer(s16 x, s16 y) {
	IngamePlatforms_DATA->playerSpritePTR = &(IngamePlatforms_DATA->sprites[0]);
	IngamePlatforms_Sprite *s = IngamePlatforms_DATA->playerSpritePTR;
	s->spriteDef = &testingame_player;
	s->position.x = x;
	s->position.y = y;
	s->size.x = 240;
	s->size.y = 320;
	s->xCenter = 120;
	s->collider.pos1.x = -120;
	s->collider.pos1.y = -200;
	s->collider.pos2.x = 120;
	s->collider.pos2.y = 0;
	s->data = 0;
	s->update = ingamePlatforms_onPlayerUpdate;
}

