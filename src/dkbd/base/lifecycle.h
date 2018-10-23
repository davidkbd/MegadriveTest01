#include <genesis.h>

// ================= Main ================= //

/**
 * Resetea metodo de update del loop.
 */
void lifecycle_resetUpdater();

/**
 * Metodo update
 */
void (*lifecycle_update)();

// ================= Stages ================= //

/**
 * Abre
 */
void lifecycle_openScreen_logoInicial();

/**
 * Abre
 */
void lifecycle_openScreen_portada();

/**
 * Abre
 */
void lifecycle_openScreen_testIngame();
void lifecycle_openScreen_ingame_platforms();
