#include "ingame_platforms.h"
#include "ingame_platforms_private.h"
#include "ingame_platforms_private_ia.h"

#include "../base/lifecycle.h"
#include "../base/hud.h"
#include "../base/event_timer_handler.h"
#include "../io/joy_handlers.h"
#include "../util/palette.h"
#include "../util/map.h"

#include "../../../res/sprite.h"
#include "../../../res/gfx.h"
#include "../base/viewport.h"

void ingamePlatforms_initializePlayer(s16 x, s16 y);
void ingamePlatforms_initializeJumper(IngameSprite *s, u8 spriteId);
void ingamePlatforms_initializeSpikes(IngameSprite *s, u8 spriteId);

// ================ INIT ================ //

void ingamePlatforms_initUI() {
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	//Esto posiciona el window abajo pero mejor vamos a hacer un hud con sprites
	//VDP_setWindowHPos(FALSE, 0);
	//VDP_setWindowVPos(TRUE, 25);

	VDP_setTextPalette(PAL3);
}

void ingamePlatforms_initMemory() {
	IngamePlatforms_DATA = MEM_alloc(sizeof(struct IngamePlatforms_ScreenData));
}

void ingamePlatforms_initData() {
	map_load(
			screensGlobal_getMapTiles(),
			screensGlobal_getMapSprites());

	for (u8 i=0; i< IngamePlatforms_NUM_SPRITES; ++i) {
		IngamePlatforms_DATA->sprites[i].sprite = 0;
	}

	IngamePlatforms_DATA->screenData.frameCount = 0;
	IngamePlatforms_DATA->screenData.sceneAnimationFrame = 0;
	IngamePlatforms_DATA->screenData.viewportOffset.x = IngamePlatforms_DATA->screenData.viewportOffset.y = 0;
	IngamePlatforms_DATA->gravity = 6;
	hud_reset();

	ingamePlatforms_initializePlayer(5, 5);

	//Jumpers
	ingamePlatforms_initializeJumper(&(IngamePlatforms_DATA->sprites[1]), 5);
	ingamePlatforms_initializeJumper(&(IngamePlatforms_DATA->sprites[2]), 6);
	ingamePlatforms_initializeJumper(&(IngamePlatforms_DATA->sprites[3]), 7);
	//Spikes
	ingamePlatforms_initializeSpikes(&(IngamePlatforms_DATA->sprites[4]), 8);
	ingamePlatforms_initializeSpikes(&(IngamePlatforms_DATA->sprites[5]), 9);
	ingamePlatforms_initializeSpikes(&(IngamePlatforms_DATA->sprites[6]), 10);

for (u8 i=7; i<16; ++i) {
	ingamePlatforms_initializeJumper(&(IngamePlatforms_DATA->sprites[i]), i+10);
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
	VDP_loadTileData(ingame_floor_tile.tiles,      G_TILEINDEX_FLOOR,        ingame_floor_tile.numTile,       FALSE);
	VDP_loadTileData(ingame_floor2_tile.tiles,     G_TILEINDEX_FLOOR2,       ingame_floor2_tile.numTile,      FALSE);
	VDP_loadTileData(ingame_background_tile.tiles, G_TILEINDEX_BACKGROUND,   ingame_background_tile.numTile,  FALSE);

	VDP_loadTileData(ingame_wall_tile.tiles,       G_TILEINDEX_WALL,         ingame_background_tile.numTile,  FALSE);

	VDP_drawImageEx(PLAN_B, &planb_level01, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_TILEINDEX_PLANB), 0, 0, TRUE, FALSE);

	viewport_initialize(
			vector2(0, 0),
			rect(0, 0, (128-40) * 160, (128-14) * 160),
			ingamePlatforms_onViewportSprite);
}

void ingamePlatforms_initSprites() {
	IngamePlatforms_DATA->hudTimeSprite.sprite = SPR_addSpriteEx(&hud_time, 5, 3, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_TIME1), 0, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	SPR_setAlwaysOnTop(IngamePlatforms_DATA->hudTimeSprite.sprite, TRUE);

	IngamePlatforms_DATA->hudScoreSprite.sprite = SPR_addSpriteEx(&hud_score, 5, 19, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_SCORE1), 1, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	SPR_setAlwaysOnTop(IngamePlatforms_DATA->hudScoreSprite.sprite, TRUE);

	IngamePlatforms_DATA->hudAnimalsSprite.sprite = SPR_addSpriteEx(&hud_animals, 265, 202, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_ITEMS1), 2, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	SPR_setAlwaysOnTop(IngamePlatforms_DATA->hudAnimalsSprite.sprite, TRUE);

	IngamePlatforms_DATA->hudLifesSprite.sprite = SPR_addSpriteEx(&hud_lifes, 5, 202, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_TILEINDEX_HUD_LIFES), 3, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);
	SPR_setAlwaysOnTop(IngamePlatforms_DATA->hudLifesSprite.sprite, TRUE);

	IngamePlatforms_DATA->sprites[0].sprite = SPR_addSpriteEx(&testingame_player, 0, 0, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, G_TILEINDEX_PLAYER), 4, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC);

}

// ================ FINALIZE ================ //

void ingamePlatforms_finalizeSound() {
}

void ingamePlatforms_finalizeGraphics() {
	SPR_releaseSprite(IngamePlatforms_DATA->hudTimeSprite.sprite);
	SPR_releaseSprite(IngamePlatforms_DATA->hudAnimalsSprite.sprite);
	SPR_releaseSprite(IngamePlatforms_DATA->hudScoreSprite.sprite);
	SPR_releaseSprite(IngamePlatforms_DATA->hudLifesSprite.sprite);
	
	for (u8 i=0; i < IngamePlatforms_NUM_SPRITES; ++i) {
		SPR_releaseSprite(IngamePlatforms_DATA->sprites[i].sprite);
	}
	VDP_clearTextArea(0, 0, 39, 27);
}

void ingamePlatforms_finalizeMemory() {
	MEM_free(IngamePlatforms_DATA);
	viewport_finalize();
}

////////////////////////////////////////////////////////

void ingamePlatforms_initializePlayer(s16 x, s16 y) {
	IngamePlatforms_DATA->playerSpritePTR = &(IngamePlatforms_DATA->sprites[0]);
	IngameSprite *s = IngamePlatforms_DATA->playerSpritePTR;
	s->spriteId = 4;
	s->position.x = x * 80;
	s->position.y = y * 80;
	s->speed.x = s->speed.y = 0;
	s->type = &INGAMESPRITE_PLAYER_TYPE;
	s->data = 0;
	s->update = ingamePlatforms_onPlayerUpdate;
}

void ingamePlatforms_initializeJumper(IngameSprite *s, u8 spriteId) {
	s->sprite = 0;
	//s->alwaysOnTop = TRUE;
	s->spriteId = spriteId;
	s->position.x = -600;
	s->position.y = -600;
	s->speed.x = s->speed.y = 0;
	s->type = &INGAMESPRITE_JUMPER_TYPE;
	s->data = 0;
	s->update = ingamePlatforms_onJumperUpdate;
}

void ingamePlatforms_initializeSpikes(IngameSprite *s, u8 spriteId) {
	s->sprite = 0;
	//s->alwaysOnTop = TRUE;
	s->spriteId = spriteId;
	s->position.x = -600;
	s->position.y = -600;
	s->speed.x = s->speed.y = 0;
	s->type = &INGAMESPRITE_SPIKES_TYPE;
	s->data = 0;
	s->update = ingamePlatforms_onSpikesUpdate;
}
