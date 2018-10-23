#include <genesis.h>

/**
 * Posiciona y dibuja todos los tiles
 */
void viewport_reset(s16 x, s16 y);

/**
 * Posiciona la vista en las coordenadas indicadas
 */
void viewport_moveX(s16 x);

/**
 * Posiciona la vista en las coordenadas indicadas
 */
void viewport_moveY(s16 y);

/**
 * Obtiene posicion horizontal.
 */
s16 viewport_getCurrentX();

/**
 * Obtiene posicion vertical.
 */
s16 viewport_getCurrentY();
