#include <genesis.h>

#include "../util/vector2.h"
#include "../util/rect.h"

/**
 * Reserva memoria, y posiciona y dibuja todos los tiles
 */
void viewport_initialize(const Vector2 *initialPoisition, Rect limits, void (*callback)(u8 spriteId, s16 x, s16 y));

/**
 * Pinta todo el contenido visible
 */
void viewport_refreshCurrentViewport();

void viewport_titleScreen();

void viewport_updateTitleScreen(u16 timer);

/**
 * Devuelve TRUE si estamos mostrando title screen
 */
u8 viewport_isTitleScreenActive();

/**
 * Libera memoria.
 */
void viewport_finalize();

/**
 * Posiciona la vista en las coordenadas indicadas
 */
void viewport_moveX(s16 x);

/**
 * Posiciona la vista en las coordenadas indicadas
 */
void viewport_moveY(s16 y);

/**
 * Refresca scroll del Plan A
 */
void viewport_planeARefresh();

/**
 * Refresca scroll del Plan B
 */
void viewport_planeBRefresh();

/**
 * Obtiene posicion horizontal.
 */
s16 viewport_getCurrentX();

/**
 * Obtiene posicion vertical.
 */
s16 viewport_getCurrentY();
