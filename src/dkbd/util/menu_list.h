#include <genesis.h>

#define MenuList_ENDMENU 0

/**
 * Funcion a la que se llama al producirse un determinado evento
 */
typedef void (*MenuList_EventCallback)(u8);
typedef void (*MenuList_RefreshCallback)(u8, u32*, u32);

/**
 * Reserva memoria y esas cosas
 */
void menuList_initialize(u32* content, MenuList_EventCallback* acceptCallbacks, MenuList_EventCallback* cancelCallbacks, u32 info);

/**
 * Libera
 */
void menuList_destroy();

/**
 * Establece callback que se llama al requerir repintado
 */
void menuList_setOnRepaintFunction(MenuList_RefreshCallback);

/**
 * Pintado
 */
void menuList_refresh();

/**
 * Selecciona item previo
 */
void menuList_up();

/**
 * Selecciona item posterior
 */
void menuList_down();

/**
 * Acepta seleccion
 */
void menuList_accept();

/**
 * Cancela seleccion
 */
void menuList_cancel();

