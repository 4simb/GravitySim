// math for gravitysim

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

float map(float x, float in_min, float in_max, float out_min, float out_max);

float crdX(float coord, int _winWidth);

float crdY(float coord, int _winHeight);