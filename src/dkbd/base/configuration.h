#include <genesis.h>

/**
 * Inicializa valores por defecto
 */
void configuration_initialize();

/**
 * Obtiene valor de opcion
 */
u8 configuration_isMusicEnabled();

/**
 * Establece valor a opcion
 */
void configuration_setMusicEnabled(u8 p);

/**
 * Obtiene valor de opcion
 */
u8 configuration_isSfxEnabled();

/**
 * Establece valor a opcion
 */
void configuration_setSfxEnabled(u8 p);

/**
 * Obtiene valor de opcion
 */
u8 configuration_getDifficulty();

/**
 * Establece valor a opcion
 */
void configuration_setDifficulty(u8 p);

/**
 * Obtiene valor de opcion
 */
u8 configuration_getButtonsMode();

/**
 * Establece valor a opcion
 */
void configuration_setButtonsMode(u8 p);
