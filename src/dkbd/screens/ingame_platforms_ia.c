#include <genesis.h>

#include <sprite_eng.h>

#include "ingame_platforms.h"
#include "ingame_platforms_private.h"
#include "ingame_platforms_private_ia.h"

#include "../base/event_timer_handler.h"
#include "../base/hud.h"
#include "../util/repeats.h"

void ingamePlatforms_onInanimatedUpdate(IngamePlatforms_Sprite *s) {
}

void ingamePlatforms_onJumperUpdate(IngamePlatforms_Sprite *s) {
	SPR_setFrame(s->sprite, 0);
}
