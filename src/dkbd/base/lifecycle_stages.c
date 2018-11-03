#include "lifecycle.h"
#include "lifecycle_private.h"

#include "screens_global.h"
#include "../screens/logo_inicial.h"
#include "../screens/portada.h"
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

void lifecycle_openScreen_ingame_platforms() {
	//screensGlobal_initialize();
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
