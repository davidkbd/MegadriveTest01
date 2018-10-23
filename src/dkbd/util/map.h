#include <genesis.h>

#define MAP_SIZE 128

/**
 * Carga datos
 */
void map_load(const u8 *mapPlanB[MAP_SIZE][MAP_SIZE], const u8 *mapPlanA[MAP_SIZE][MAP_SIZE]);

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
u8 map_getRestriction(u8 x, u8 y);

/**
 * Obtiene la posicion Y en la que un tile ya es on top. La posicion es relativa al borde superior de la pantalla.
 */
u8 map_getOnTop(u8 tileId);
