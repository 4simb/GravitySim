#pragma once
#include "Vector2d.h"
#include "Force.h"
#include "GravitySim.h"

class CosmicBody {
public:
	CosmicBody();
	CosmicBody(CosmicBody* _cosmicBody);
	CosmicBody(float _mass, float _radius, float _xSpeed = 0.f, float _ySpeed = 0.f, glColor _color = {0.5f, 0.5f, 0.5f});
	CosmicBody(float _mass, float _radius, float _xSpeed, float _ySpeed, glColor _innerColor, glColor _externColor);
	CosmicBody(float _mass, float _radius, Vector2d _speed, glColor _color = {0.5f, 0.5f, 0.5f});
	CosmicBody(float _mass, float _radius, Vector2d _speed, glColor _innerColor, glColor _externColor);

	double getMass();
	float getRadius();
	glColor getInnerColor();
	glColor getExternColor();
	Vector2d getSpeed();

	virtual void applyForce(Force _force);

	~CosmicBody();

private:
	double m_mass;
	float m_radius;
	glColor m_innerColor;
	glColor m_externColor;
	Vector2d m_speed;
};