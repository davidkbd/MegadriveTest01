#include <genesis.h>

/**
 * Pone a 0
 */
void hud_reset();

/**
 * Actualiza valores al estado inicial
 */
void hud_init();

/**
 * Actualiza valores y cambia elementos visuales
 */
void hud_updateTimer();

/**
 * Actualiza valor y cambia elementos visuales
 */
void hud_updateScore();

/**
 * Actualiza valores y cambia elementos visuales
 */
void hud_updateLifes();

/**
 * Devuelve el tiempo actual (segundos)
 */
u32 hud_getTimeSeconds();

/**
 * Devuelve el tiempo inicial (milisegundos)
 */
u32 hud_getInitialTimeMS();
