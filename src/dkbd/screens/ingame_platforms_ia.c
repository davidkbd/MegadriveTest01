#include <genesis.h>

#include "ingame_platforms.h"
#include "ingame_platforms_private.h"
#include "ingame_platforms_private_ia.h"

#include "../base/event_timer_handler.h"
#include "../base/hud.h"
#include "../util/repeats.h"
#include "../util/collision.h"

void ingamePlatforms_onInanimatedUpdate(IngamePlatforms_Sprite *s) {
}

void ingamePlatforms_onJumperUpdate(IngamePlatforms_Sprite *s) {
	if (s->sprite == 0) {
		return;
	}
	// s->data = animation position
	IngamePlatforms_Sprite *player = IngamePlatforms_DATA->playerSpritePTR;
	player->pushing = 0;
	while (collision_checkRectVsRect(&(player->footsCollider), &(s->footsCollider))) {
		s8 displace;
		if (player->position.x + player->xCenter < s->position.x + s->xCenter) {
			displace = -1;
		} else {
			displace = 1;
		}
		ingamePlatforms_moveXSprite(player, displace);
		player->pushing = 1;
	}
	if (collision_checkRectVsRect(&(s->collider), &(player->footsCollider)) || s->data != 0) {
		if (s->data < 8) {
			++s->data;
		} else {
			s->data = 0;
		}
		player->speed.y = INGAME_PLATFORMS_MAX_JUMP_SPEED;
	}
	SPR_setAnimAndFrame(s->sprite, 0, s->data/2);
}
