#include "Force.h"

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