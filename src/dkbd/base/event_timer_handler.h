#include <genesis.h>

/**
 * Establece valores a un estado inicial.
 */
void eventTimerHandler_reset();

/**
 * Asigna un callback a un slot.
 */
void eventTimerHandler_addSlot(u16 time, void (*callback)());

/**
 * Activa
 */
void eventTimerHandler_enable();

/**
 * Desactiva
 */
void eventTimerHandler_disable();

/**
 * Comprueba si esta activo
 */
u8 eventTimerHandler_isEnabled();

/**
 * Ejecucion
 */
void (*eventTimerHandler_update)();
