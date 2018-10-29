#include "vector2.h"

Vector2 vector2(s16 x, s16 y) {
	Vector2 v;
	v.x = x;
	v.y = y;
	return v;
}

Vector2 vector2_add(Vector2 *value, Vector2 *otherValue) {
	Vector2 v;
	v.x = value->x + otherValue->x;
	v.y = value->y + otherValue->y;
	return v;
}
