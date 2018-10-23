#include "rect.h"

Rect rect_add(Rect *value, Rect *otherValue) {
	Rect r = *value;
	r.pos1 = vector2_add(&(r.pos1), &(otherValue->pos1));
	r.pos2 = vector2_add(&(r.pos2), &(otherValue->pos2));
	return r;
}

Rect rect_addVector2(Rect *value, Vector2 *oneVector) {
	Rect r;
	r.pos1 = vector2_add(&(value->pos1), oneVector);
	r.pos2 = value->pos2;
	return r;
}

Rect rect_addTwoVector2(Rect *value, Vector2 *oneVector, Vector2 *otherVector) {
	Rect r;
	r.pos1 = vector2_add(&(value->pos1), oneVector);
	r.pos2 = vector2_add(&(value->pos2), otherVector);
	return r;
}
