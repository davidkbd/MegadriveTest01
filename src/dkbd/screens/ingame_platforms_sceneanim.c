#include "ingame_platforms_private_sceneanim.h"

#include "../util/repeats.h"
#include "../util/palette.h"

#include "../../../res/gfx.h"

void ingamePlatforms_updateSubFloorAnimation();

void ingamePlatforms_updateSceneAnimation() {
	if (repeats_delayed(IngamePlatforms_DATA->screenData.frameCount, 0, 0, repeats_1_each_2_mode)) {
		++IngamePlatforms_DATA->screenData.sceneAnimationFrame;
		if (IngamePlatforms_DATA->screenData.sceneAnimationFrame > 3) {
			IngamePlatforms_DATA->screenData.sceneAnimationFrame = 0;
		}
		ingamePlatforms_updateSubFloorAnimation();
	}
}

void ingamePlatforms_updateSubFloorAnimation() {
	switch (IngamePlatforms_DATA->screenData.sceneAnimationFrame) {
		case 3:
			palette_putColor(PAL3, 2, 0xa66);
			palette_putColor(PAL3, 3, 0x944);
			palette_putColor(PAL3, 4, 0x833);
			palette_putColor(PAL3, 5, 0x722);
			break;
		case 2:
			palette_putColor(PAL3, 2, 0x722);
			palette_putColor(PAL3, 3, 0xa66);
			palette_putColor(PAL3, 4, 0x944);
			palette_putColor(PAL3, 5, 0x833);
			break;
		case 1:
			palette_putColor(PAL3, 2, 0x833);
			palette_putColor(PAL3, 3, 0x722);
			palette_putColor(PAL3, 4, 0xa66);
			palette_putColor(PAL3, 5, 0x944);
			break;
		case 0:
			palette_putColor(PAL3, 2, 0x944);
			palette_putColor(PAL3, 3, 0x833);
			palette_putColor(PAL3, 4, 0x722);
			palette_putColor(PAL3, 5, 0xa66);
			break;
	
	}
	palette_apply();
}
