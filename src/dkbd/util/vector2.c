#include "vector2.h"

Vector2 vector2(s16 x, s16 y) {
	Vector2 v = {x,y};
	return v;
}

Vector2 vector2_add(Vector2 *value, Vector2 *otherValue) {
	Vector2 v = {
		value->x + otherValue->x,
		value->y + otherValue->y};
	return v;
}
