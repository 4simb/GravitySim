#include "CosmicBody.h"

CosmicBody::CosmicBody()
{
	m_mass = 0.f;
	m_radius = 0.f;
	m_speed = Vector2d(0, 0);
	m_innerColor = m_externColor = glColor{0.5468f, 0.7734f, 0.2460f};
}

CosmicBody::CosmicBody(CosmicBody* _cosmicBody)
{
	m_mass = _cosmicBody->getMass();
	m_radius = _cosmicBody->getRadius();
	m_speed = _cosmicBody->getSpeed();
	m_innerColor = _cosmicBody->getInnerColor();
	m_externColor = _cosmicBody->getExternColor();
}

CosmicBody::CosmicBody(float _mass, float _radius, float _xSpeed, float _ySpeed, glColor _color)
{
	m_mass = _mass;
	m_radius = _radius;
	m_speed = Vector2d(_xSpeed, _ySpeed);
	m_innerColor = m_externColor = _color;
}

CosmicBody::CosmicBody(float _mass, float _radius, float _xSpeed, float _ySpeed, glColor _innerColor, glColor _externColor)
{
	m_mass = _mass;
	m_radius = _radius;
	m_speed = Vector2d(_xSpeed, _ySpeed);
	m_innerColor = _innerColor;
	m_externColor = _externColor;
}

CosmicBody::CosmicBody(float _mass, float _radius, Vector2d _speed, glColor _color)
{
	m_mass = _mass;
	m_radius = _radius;
	m_speed = _speed;
	m_innerColor = m_externColor = _color;
}

CosmicBody::CosmicBody(float _mass, float _radius, Vector2d _speed, glColor _innerColor, glColor _externColor)
{
	m_mass = _mass;
	m_radius = _radius;
	m_speed = _speed;
	m_innerColor = _innerColor;
	m_externColor = _externColor;
}

double CosmicBody::getMass()
{
	return m_mass;
}

float CosmicBody::getRadius()
{
	return m_radius;
}

glColor CosmicBody::getInnerColor()
{
	return m_innerColor;
}

glColor CosmicBody::getExternColor()
{
	return m_externColor;
}

Vector2d CosmicBody::getSpeed()
{
	return m_speed;
}

void CosmicBody::applyForce(Force _force)
{
	// a = F/m
	m_speed.setX(m_speed.getX() + _force.getX() / m_mass);
	m_speed.setY(m_speed.getY() + _force.getY() / m_mass);
}

CosmicBody::~CosmicBody()
{
	;
}
