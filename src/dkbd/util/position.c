#include "position.h"

u8 position_isRectInRect(Rect *rect1, Rect *rect2) {
	Vector2 *posUL = &(rect1->pos1);
	Vector2 posUR = rect1->pos1;
	Vector2 posBR = rect1->pos1;
	Vector2 posBL = rect1->pos1;
	
	posUR.x += rect1->pos2.x;
	posBR.x += rect1->pos2.x;
	posBR.y += rect1->pos2.y;
	posBL.y += rect1->pos2.y;
	
	return position_isInRect(posUL, rect2)
		|| position_isInRect(&posUR, rect2)
		|| position_isInRect(&posBR, rect2)
		|| position_isInRect(&posBL, rect2);
}

u8 position_isInRect(Vector2 *pos, Rect *rect) {
	return pos->x >= rect->pos1.x
		&& pos->x < rect->pos1.x + rect->pos2.x
		&& pos->y >= rect->pos1.y
		&& pos->y < rect->pos1.y + rect->pos2.y;
}

