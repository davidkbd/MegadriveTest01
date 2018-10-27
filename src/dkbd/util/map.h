#include <genesis.h>

#define MAP_WIDTH 128
#define MAP_HEIGHT 128

#define MAP_RESTRICTION_UP              0b0000000000000001
#define MAP_RESTRICTION_RIGHT           0b0000000000000010
#define MAP_RESTRICTION_DOWN            0b0000000000000100
#define MAP_RESTRICTION_LEFT            0b0000000000001000

// Es una rampa
#define MAP_RESTRICTION_ISRAMP          0b0000000100000000
// Invertido
#define MAP_RESTRICTION_ISRAMPLEFT      0b0000000010000000
// Es el tile inferior a la rampa
#define MAP_RESTRICTION_ISBOTTOMTILE    0b0000000001000000
// Inclinacion fuerte
#define MAP_RESTRICTION_ISRAMPHARD      0b0000000000100000
// Esta desplazado 50% para abajo
#define MAP_RESTRICTION_ISRAMPDISPLACED 0b0000000000010000

/**
 * Carga datos
 */
void map_load(const u8 * (*mapPlanA)[MAP_WIDTH]);

/**
 * Libera memoria
 */
void map_destroy();

/**
 * Obtiene ancho del mapa en memoria
 */
u8 map_getWidth();

/**
 * Obtiene altura del mapa en memoria
 */
u8 map_getHeight();

/**
 * Obtiene el tile del mapa en memoria dada la posicion
 */
u8 map_getPlanA(u8 x, u8 y);

/**
 * Obtiene el tile del mapa en memoria dada la posicion
 */
u8 map_getPlanB(u8 x, u8 y);

/**
 * Obtiene las restricciones dada la posicion
 */
u16 map_getRestriction(u8 x, u8 y);

/**
 * Obtiene la posicion Y en la que un tile ya es on top. La posicion es relativa al borde superior de la pantalla.
 */
u8 map_getOnTop(u8 tileId);
