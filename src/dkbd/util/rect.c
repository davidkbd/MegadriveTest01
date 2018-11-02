#include "rect.h"

Rect rect(s16 x1, s16 y1, s16 x2, s16 y2) {
	Rect r;
	r.pos1.x = x1;
	r.pos1.y = y1;
	r.pos2.x = x2;
	r.pos2.y = y2;
	return r;
}
