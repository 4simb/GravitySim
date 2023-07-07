// graphics functions for gravitysim

#pragma once

#include <GL/glut.h>
#include <iostream>

#include "GravitySimMath.h"

#define WIN_WIDTH 1900
#define WIN_HEIGHT 1000

struct winSize;

struct glColor;

void glPoint(float x, float y);

void drawEmptyCircle(float x, float y, float r, int w);

void drawCircle(float x, float y, float r, glColor innerColor, glColor externColor);

void drawCircle(float x, float y, float r, glColor color);

void drawString(float x, float y, const char* string);

void drawString(float x, float y, char* string);

void drawString(float x, float y, std::string string);