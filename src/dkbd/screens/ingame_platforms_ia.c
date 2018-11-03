#include <genesis.h>

#include "ingame_platforms.h"
#include "ingame_platforms_private.h"
#include "ingame_platforms_private_ia.h"

#include "../base/event_timer_handler.h"
#include "../base/hud.h"
#include "../util/repeats.h"
#include "../util/collision.h"

u8 ingamePlatforms_iaIsNear(IngameSprite *sprite1, IngameSprite *sprite2);

void ingamePlatforms_onInanimatedUpdate(IngameSprite *s) {
}

void ingamePlatforms_onJumperUpdate(IngameSprite *s) {
	// s->data = animation position
	IngameSprite *player = IngamePlatforms_DATA->playerSpritePTR;
	if (ingamePlatforms_iaIsNear(player, s)) {
		Rect playerFootsCollider = ingameSprite_calculateFootsCollider(player);
		Rect jumperFootsCollider = ingameSprite_calculateFootsCollider(s);
		Rect jumperCollider      = ingameSprite_calculeCollider(s);
		while (collision_checkRectVsRect(&playerFootsCollider, &jumperFootsCollider)) {
			s8 displace = (ingameSprite_compareXPosition(player, s) < 0)? -1 : 1;
			ingameSprite_moveX(player, displace);
			playerFootsCollider.pos1.x += displace;
			playerFootsCollider.pos2.x += displace;
		}
		if (player->speed.y > 0 && collision_checkRectVsRect(&jumperCollider, &playerFootsCollider)) {
			s->data = 1;
		}
	}
	if (s->data != 0) {
		if (s->data < 8) {
			++s->data;
		} else {
			s->data = 0;
		}
		player->speed.y = INGAME_PLATFORMS_MAX_JUMP_SPEED;
	}
	SPR_setAnimAndFrame(s->sprite, 0, s->data/2);
}

void ingamePlatforms_onSpikesUpdate(IngameSprite *s) {
	IngameSprite *player = IngamePlatforms_DATA->playerSpritePTR;
	if (ingamePlatforms_iaIsNear(player, s)) {
		Rect playerFootsCollider = ingameSprite_calculateFootsCollider(player);
		Rect jumperFootsCollider = ingameSprite_calculateFootsCollider(s);
		Rect jumperCollider      = ingameSprite_calculeCollider(s);
		while (collision_checkRectVsRect(&playerFootsCollider, &jumperFootsCollider)) {
			s8 displace = (ingameSprite_compareXPosition(player, s) < 0)? -1 : 1;
			ingameSprite_moveX(player, displace);
			playerFootsCollider.pos1.x += displace;
			playerFootsCollider.pos2.x += displace;
		}
		if (player->speed.y > 0 && collision_checkRectVsRect(&jumperCollider, &playerFootsCollider)) {
			ingamePlatforms_beginExit();
		}
	}
}

u8 ingamePlatforms_iaIsNear(IngameSprite *sprite1, IngameSprite *sprite2) {
	return abs(sprite1->position.x - sprite2->position.x) < 400 && abs(sprite1->position.y - sprite2->position.y) < 400;
}
