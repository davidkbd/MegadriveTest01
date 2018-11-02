#include <genesis.h>

void executeEventCallback(MenuList_EventCallback, u8);

/**
 * Memoria reservada
 */
struct MenuList_DATA_st {
	/**
	 * Item seleccionado
	 */
	u8 selected;

	/**
	 * Para almacenar la pantalla por ejemplo
	 */
	u32 info;

	/**
	 * Callback repaint
	 */
	MenuList_RefreshCallback refreshCallback;
	
	/**
	 * Tabla de opciones
	 */
	u32* options;

	/**
	 * Tabla de callbacks Aceptar
	 */
	MenuList_EventCallback* acceptCallbacks;

	/**
	 * Tabla de callbacks Cancelar
	 */
	MenuList_EventCallback* cancelCallbacks;
} *MenuList_DATA = NULL;

