#include "GravitySimMath.h"

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float crdX(float coord, int _winWidth) {
	return map(coord, 0, _winWidth, -1, 1);
}

float crdY(float coord, int _winHeight) {
	return map(coord, 0, _winHeight, -1, 1);
}