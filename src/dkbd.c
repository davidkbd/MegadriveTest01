#include <genesis.h>

#include "dkbd/base/lifecycle.h"
#include "dkbd/base/configuration.h"

#include "dkbd/base/fpsfixer.h"

#include "gfx.h"
#include "dinamicimages.h"

int dkbd() {
	configuration_initialize();
	
	JOY_init();
	JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
	//Los otros valores correspondientes al resto de controles soportados
	//en las librerías SGDK son JOY_SUPPORT_OFF, JOY_SUPPORT_3BTN,
	//JOY_SUPPORT_MOUSE, JOY_SUPPORT_TRACKBALL, JOY_SUPPORT_TEAMPLAYER,
	//JOY_SUPPORT_EA4WAYPLAY, JOY_SUPPORT_MENACER, JOY_SUPPORT_JUSTIFIER_BLUE,
	//JOY_SUPPORT_JUSTIFIER_BOTH, JOY_SUPPORT_ANALOGJOY, JOY_SUPPORT_KEYBOARD

	SYS_disableInts();
	//SYS_enableInts();

	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);

	VDP_setScreenWidth320();
	VDP_setScreenHeight224();

	SPR_init(16, 256, 256);
	SYS_enableInts();

	VDP_setWindowAddress(0xD000);
	VDP_setAPlanAddress(0xC000);
	VDP_setBPlanAddress(0xE000);
	VDP_setSpriteListAddress(0xF000);
	VDP_setHScrollTableAddress(0xF800);
	
//	
//	Circulo c = {2800,320,160,160};
//	Rectangulo r = {1522,450,320,3};
//	
//	KLog_U1("c ", collision_circleRect(&c, &r));
//	waitMs(15000);
	
//	for (int i=0; i<16; ++i) {
//		printTextAndLong(PLAN_A, "", palette1_image.palette->data[i], 0, i);
//		// red   4F16
//		// green 4ef6
//		// blue  4ed6
//	}
//	waitMs(2000);

	lifecycle_resetUpdater();
	
	//lifecycle_openScreen_logoInicial();
	lifecycle_openScreen_ingame_platforms();
	//GAME_PERSISTENT_DATA.player.checkPointsCount = 5;
	//lifecycle_playGame();
	while (1) {
		u32 currentTimeMillis = getTimeAsFix32(FALSE);
		lifecycle_update();
		SPR_update();
		VDP_waitVSync();
		fpsfixer_fixTo30FPS(currentTimeMillis);
	}
	return 0; 
}

