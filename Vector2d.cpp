#include <math.h>
#include "Vector2d.h"

Vector2d::Vector2d()
{
	m_x = 0;
	m_y = 0;
}

Vector2d::Vector2d(float _x, float _y)
{
	m_x = _x;
	m_y = _y;
}

Vector2d::Vector2d(Vector2d* _vector)
{
	m_x = _vector->m_x;
	m_y = _vector->m_y;
}

float Vector2d::getX()
{
	return m_x;
}

float Vector2d::getY()
{
	return m_y;
}

float Vector2d::module()
{
	return sqrt(m_x * m_x + m_y + m_y);
}

void Vector2d::normalize()
{
	float mod = module();
	m_x /= mod;
	m_y /= mod;
}

void Vector2d::setX(float _x)
{
	m_x = _x;
}

void Vector2d::setY(float _y)
{
	m_y = _y;
}

Vector2d::~Vector2d()
{
	;
}