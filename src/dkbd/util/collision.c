#include "collision.h"

u8 collision_checkRectVsVector2(Rect *rect1, Vector2 *vector2) {
	return
			vector2->y >= rect1->pos1.y &&
			vector2->y <= rect1->pos2.y &&
			vector2->x >= rect1->pos1.x &&
			vector2->x <= rect1->pos2.x;
}

u8 collision_checkRectVsRect(Rect *rect1, Rect *rect2) {
	if (collision_checkRectVsVector2(rect1, &(rect2->pos1)) || collision_checkRectVsVector2(rect1, &(rect2->pos2))) {
		return 1;
	}
	Vector2 ur = vector2(rect2->pos2.x, rect2->pos1.y);
	if (collision_checkRectVsVector2(rect1, &ur)) {
		return 1;
	}
	Vector2 bl = vector2(rect2->pos1.x, rect2->pos2.y);
	if (collision_checkRectVsVector2(rect1, &bl)) {
		return 1;
	}
	return 0;
}
