#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

//struct glColor {
//	float m_red;
//	float m_green;
//	float m_blue;
//	float m_alpha = 1.f;
//};

#include "GravitySimMath.h"
#include "GravitySimGraphics.h"
#include "CosmicBody.h"
#include "Vector2d.h"
#include "Force.h"

void renderBody(CosmicBody* body)
{
	drawCircle(body->getXpos() * 2, body->getYpos() * 2, body->getRadius(), body->getInnerColor(), body->getExternColor());
}