#include <genesis.h>

#include "rect.h"
#include "vector2.h"

/**
 * Comprueba si vector2 se encuentra dentro de rect1
 */
u8 collision_checkRectVsVector2(Rect *rect1, Vector2 *vector2);

/**
 * Comprueba si rect1 y rect2 se tocan
 */
u8 collision_checkRectVsRect(Rect *rect1, Rect *rect2);
