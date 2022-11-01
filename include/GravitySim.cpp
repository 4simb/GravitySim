#include "GravitySim.h"
#include <math.h>

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

Force::Force(Vector2d* _vector, float _value)
{
	setX(_vector->getX());
	setY(_vector->getY());
	m_value = _value;
}

Force::Force(float _x, float _y, float _value)
{
	setX(_x);
	setY(_y);
	m_value = _value;
}

Force::Force(Force* _force)
{
	setX(_force->getX());
	setY(_force->getY());
	m_value = _force->m_value;
}

void Force::normalize()
{
	float mod = module() / m_value;
	//m_x /= mod;
	//m_y /= mod;
	setX(getX() / mod);
	setY(getY() / mod);
}

Force::~Force()
{
	;
}
