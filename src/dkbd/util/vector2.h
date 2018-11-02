#include <genesis.h>

#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct Vector2_st {
	s16 x;
	s16 y;
} Vector2;

#endif

/**
 * Crea un vector nuevo
 */
Vector2 vector2(s16 x, s16 y);

/**
 * Devuelve un nuevo vectro con el resultado de sumar los dos
 */
Vector2 vector2_add(Vector2 *value, Vector2 *otherValue);
