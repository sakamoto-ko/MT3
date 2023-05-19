#include "base.h"

int GetColor(unsigned int red, unsigned int  green, unsigned int  blue, int  alpha) {
	int color = (red << 24) | (green << 16) | (blue << 8) | alpha;
	return color;
}

float Cot(float a) {
	float result;

	result = 1 / tanf(a);

	return result;
}