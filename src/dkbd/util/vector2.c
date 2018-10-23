#include "vector2.h"

Vector2 vector2_add(Vector2 *value, Vector2 *otherValue) {
	Vector2 v;
	v.x = value->x + otherValue->x;
	v.y = value->y + otherValue->y;
	return v;
}
