#include "lifecycle.h"
#include "lifecycle_private.h"

#include "../screens/logo_inicial.h"
#include "../screens/portada.h"
#include "../screens/testingame.h"
#include "../screens/ingame_platforms.h"

void lifecycle_openScreen_logoInicial() {
	lifecycle_changeScreen(logoInicial_initialize, logoInicial_update);
	lifecycle_configureControls(
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyPressFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction,
			logoInicial_onKeyReleaseFunction
			);
}

void lifecycle_openScreen_portada() {
	lifecycle_changeScreen(portada_initialize, portada_update);
	lifecycle_configureControls(
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyPressFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction,
			portada_onKeyReleaseFunction
			);
}

void lifecycle_openScreen_testIngame() {
	lifecycle_changeScreen(testIngame_initialize, testIngame_update);
	lifecycle_configureControls(
			testIngame_onKeyPressStartFunction,
			testIngame_onKeyPressAFunction,
			testIngame_onKeyPressBFunction,
			testIngame_onKeyPressCFunction,
			testIngame_onKeyPressXFunction,
			testIngame_onKeyPressYFunction,
			testIngame_onKeyPressZFunction,
			testIngame_onKeyPressUpFunction,
			testIngame_onKeyPressDownFunction,
			testIngame_onKeyPressLeftFunction,
			testIngame_onKeyPressRightFunction,
			testIngame_onKeyReleaseStartFunction,
			testIngame_onKeyReleaseAFunction,
			testIngame_onKeyReleaseBFunction,
			testIngame_onKeyReleaseCFunction,
			testIngame_onKeyReleaseXFunction,
			testIngame_onKeyReleaseYFunction,
			testIngame_onKeyReleaseZFunction,
			testIngame_onKeyReleaseUpFunction,
			testIngame_onKeyReleaseDownFunction,
			testIngame_onKeyReleaseLeftFunction,
			testIngame_onKeyReleaseRightFunction
			);
}


void lifecycle_openScreen_ingame_platforms() {
	lifecycle_changeScreen(ingamePlatforms_initialize, ingamePlatforms_update);
	lifecycle_configureControls(
			ingamePlatforms_onKeyPressStartFunction,
			ingamePlatforms_onKeyPressAFunction,
			ingamePlatforms_onKeyPressBFunction,
			ingamePlatforms_onKeyPressCFunction,
			ingamePlatforms_onKeyPressXFunction,
			ingamePlatforms_onKeyPressYFunction,
			ingamePlatforms_onKeyPressZFunction,
			ingamePlatforms_onKeyPressUpFunction,
			ingamePlatforms_onKeyPressDownFunction,
			ingamePlatforms_onKeyPressLeftFunction,
			ingamePlatforms_onKeyPressRightFunction,
			ingamePlatforms_onKeyReleaseStartFunction,
			ingamePlatforms_onKeyReleaseAFunction,
			ingamePlatforms_onKeyReleaseBFunction,
			ingamePlatforms_onKeyReleaseCFunction,
			ingamePlatforms_onKeyReleaseXFunction,
			ingamePlatforms_onKeyReleaseYFunction,
			ingamePlatforms_onKeyReleaseZFunction,
			ingamePlatforms_onKeyReleaseUpFunction,
			ingamePlatforms_onKeyReleaseDownFunction,
			ingamePlatforms_onKeyReleaseLeftFunction,
			ingamePlatforms_onKeyReleaseRightFunction
			);
}
