#include <genesis.h>

#include "../util/vector2.h"
#include "../util/rect.h"

/**
 * Posiciona y dibuja todos los tiles
 */
void viewport_reset(Vector2 initialPoisition, Rect limits);

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
