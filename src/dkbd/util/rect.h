#include <genesis.h>

#include "vector2.h"

#ifndef RECT_H
#define RECT_H

typedef struct Rect_st {
	Vector2 pos1;
	Vector2 pos2;
} Rect;

#endif

/**
 * Crea un rect nuevo
 */
Rect rect(s16 x1, s16 y1, s16 x2, s16 y2);
