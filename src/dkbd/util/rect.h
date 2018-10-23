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
 * Devuelve un nuevo vectro con el resultado de sumar los dos
 */
Rect rect_add(Rect *value, Rect *otherValue);

/**
 * Devuelve un nuevo vectro con el resultado de sumar los dos
 */
Rect rect_addVector2(Rect *value, Vector2 *oneVector);

/**
 * Devuelve un nuevo vectro con el resultado de sumar los dos
 */
Rect rect_addTwoVector2(Rect *value, Vector2 *oneVector, Vector2 *otherVector);
