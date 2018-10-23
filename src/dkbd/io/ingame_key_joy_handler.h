#include <genesis.h>

/**
 * Manejador
 */
void ingameKeyJoyHandler( u16 joy, u16 changed, u16 state);

void (*onKeyPressStartFunction)(u16);
void (*onKeyPressAFunction)(u16);
void (*onKeyPressBFunction)(u16);
void (*onKeyPressCFunction)(u16);
void (*onKeyPressXFunction)(u16);
void (*onKeyPressYFunction)(u16);
void (*onKeyPressZFunction)(u16);
void (*onKeyPressUpFunction)(u16);
void (*onKeyPressDownFunction)(u16);
void (*onKeyPressLeftFunction)(u16);
void (*onKeyPressRightFunction)(u16);
void (*onKeyReleaseStartFunction)(u16);
void (*onKeyReleaseAFunction)(u16);
void (*onKeyReleaseBFunction)(u16);
void (*onKeyReleaseCFunction)(u16);
void (*onKeyReleaseXFunction)(u16);
void (*onKeyReleaseYFunction)(u16);
void (*onKeyReleaseZFunction)(u16);
void (*onKeyReleaseUpFunction)(u16);
void (*onKeyReleaseDownFunction)(u16);
void (*onKeyReleaseLeftFunction)(u16);
void (*onKeyReleaseRightFunction)(u16);
