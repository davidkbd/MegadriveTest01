#include "event_timer_handler.h"

#define EVENT_TIMER_HANDLER_PRIVATE_MAX_SLOTS 10

/**
 * Datos de cada slot
 */
typedef struct EventTimerHandler_Slot_st {
	u16 time;
	void (*callback)();
} EventTimerHandler_Slot;

/**
 * Datos internos del manejador de eventos
 */
struct EventTimerHandler_DATA_st {
	/**
	 * Temporizador
	 */
	u16 timer;
	/**
	 * Posicion actual
	 */
	u8 slot_position;
	/**
	 * Numero de slots configurados
	 */
	u8 numSlots;
	/**
	 * Lista de slots. No la hacemos dinamica porque no ocupa demasiado
	 * y no ocupa mucho en memoria
	 */
	EventTimerHandler_Slot slots[EVENT_TIMER_HANDLER_PRIVATE_MAX_SLOTS];
} EventTimerHandler_DATA;

/**
 * Ejecucion en modo activado.
 */
void eventTimerHandler_execute();
/**
 * Ejecucion vacia, se ha excedido el tiempo del ultimo slot.
 */
void eventTimerHandler_doNothing();

