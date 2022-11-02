#include <iostream>
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

CosmicBody::CosmicBody(float _xpos, float _ypos, float _mass, float _radius, float _xSpeed, float _ySpeed, glColor _color)
{
	m_xpos = _xpos;
	m_ypos = _ypos;
	m_mass = _mass;
	m_radius = _radius;
	m_speed = Vector2d(_xSpeed, _ySpeed);
	m_innerColor = m_externColor = _color;
}

CosmicBody::CosmicBody(float _xpos, float _ypos, float _mass, float _radius, float _xSpeed, float _ySpeed, glColor _innerColor, glColor _externColor)
{
	m_xpos = _xpos;
	m_ypos = _ypos;
	m_mass = _mass;
	m_radius = _radius;
	m_speed = Vector2d(_xSpeed, _ySpeed);
	m_innerColor = _innerColor;
	m_externColor = _externColor;
}

CosmicBody::CosmicBody(float _xpos, float _ypos, float _mass, float _radius, Vector2d _speed, glColor _color)
{
	m_xpos = _xpos;
	m_ypos = _ypos;
	m_mass = _mass;
	m_radius = _radius;
	m_speed = _speed;
	m_innerColor = m_externColor = _color;
}

CosmicBody::CosmicBody(float _xpos, float _ypos, float _mass, float _radius, Vector2d _speed, glColor _innerColor, glColor _externColor)
{
	m_xpos = _xpos;
	m_ypos = _ypos;
	m_mass = _mass;
	m_radius = _radius;
	m_speed = _speed;
	m_innerColor = _innerColor;
	m_externColor = _externColor;
}

float CosmicBody::getXpos()
{
	return m_xpos;
}

float CosmicBody::getYpos()
{
	return m_ypos;
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

bool CosmicBody::isMoovable()
{
	return m_moovable;
}

void CosmicBody::setXpos(float _xpos)
{
	m_xpos = _xpos;
}

void CosmicBody::setYpod(float _ypos)
{
	m_ypos = _ypos;
}

void CosmicBody::setMass(float _mass)
{
	if (_mass > 0)m_mass = _mass;
}

void CosmicBody::setRadius(float _radius)
{
	if (_radius > 0) m_radius = _radius;
}

void CosmicBody::setColor(glColor _color)
{
	m_innerColor = m_externColor = _color;
}

void CosmicBody::setInnerCoolor(glColor _innerColor)
{
	m_innerColor = _innerColor;
}

void CosmicBody::setExternColor(glColor _externColor)
{
	m_externColor = _externColor;
}

void CosmicBody::setSpeed(Vector2d _speed)
{
	m_speed = _speed;
}

void CosmicBody::setSpeed(float _xspeed, float _yspeed)
{
	m_speed.setX(_xspeed);
	m_speed.setY(_yspeed);
}

void CosmicBody::setMoovable(bool _moovable)
{
	m_moovable = _moovable;
}

void CosmicBody::proceed()
{
	if (!this->isMoovable()) return;
	m_xpos += m_speed.getX();
	m_ypos += m_speed.getY();
	//std::cout << m_xpos << "\t" << m_ypos << "\n";
}

void CosmicBody::applyForce(Force* _force)
{
	// a = F/m
	if (!this->isMoovable()) return;
	m_speed.setX(m_speed.getX() + _force->getX() / m_mass);
	m_speed.setY(m_speed.getY() + _force->getY() / m_mass);
}

CosmicBody::~CosmicBody()
{
	;
}
