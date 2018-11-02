#include <genesis.h>

/**
 * Comprueba si hay pulsacion y ejecuta
 */
void ingameKeyJoyHandler_checkAndExec(u16 joy, u16 changed, u16 state, u16 key, void(*pressFunction)(u16), void(*releaseFunction)(u16));
