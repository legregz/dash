#include "../inc/utils.hpp"

void scaleRect(int *x, int *y, int *w, int *h, int GAP[2], double RATIO) {
	*x *= RATIO;
	*x += GAP[0];
	*y *= RATIO;
	*y += GAP[1];
	*w *= RATIO;
	*h *= RATIO;
}
