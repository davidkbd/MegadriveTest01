#include "ingame_platforms_private_sceneanim.h"

#include "../util/repeats.h"
#include "../util/palette.h"

#include "../../../res/gfx.h"

void ingamePlatforms_updateSubFloorAnimation();

void ingamePlatforms_updateSceneAnimation() {
	if (repeats_delayed(IngamePlatforms_DATA->screenData.frameCount, 0, 0, repeats_1_each_5_mode)) {
		++IngamePlatforms_DATA->screenData.sceneAnimationFrame;
		if (IngamePlatforms_DATA->screenData.sceneAnimationFrame > 2) {
			IngamePlatforms_DATA->screenData.sceneAnimationFrame = 0;
		}
		ingamePlatforms_updateSubFloorAnimation();
	}
}

void ingamePlatforms_updateSubFloorAnimation() {
	switch (IngamePlatforms_DATA->screenData.sceneAnimationFrame) {
		case 2:
			palette_putColor(PAL1, 2, 0xf33);
			palette_putColor(PAL1, 3, 0xf55);
			palette_putColor(PAL1, 4, 0xe00);
			break;
		case 1:
			palette_putColor(PAL1, 2, 0xf55);
			palette_putColor(PAL1, 3, 0xe00);
			palette_putColor(PAL1, 4, 0xf33);
			break;
		case 0:
			palette_putColor(PAL1, 2, 0xe00);
			palette_putColor(PAL1, 3, 0xf33);
			palette_putColor(PAL1, 4, 0xf55);
			break;
	}
	palette_apply();
}
