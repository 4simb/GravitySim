#pragma once
//#include "Vector2d.h"
//#include "Force.h"
//#include "GravitySim.h"

#include "Vector2d.h"
#include "Force.h"
#include "GravitySimGraphics.h"

#define UNMOVABLE 0b10000000

class CosmicBody {
public:
	CosmicBody();
	CosmicBody(CosmicBody* _cosmicBody);
	CosmicBody(float _xPos, float _yPos, float _mass, float _radius, float _xSpeed = 0.f, float _ySpeed = 0.f, glColor _color = { 0.5f, 0.5f, 0.5f }, uint8_t FLAG = 0b0);
	CosmicBody(float _xPos, float _yPos, float _mass, float _radius, float _xSpeed, float _ySpeed, glColor _innerColor, glColor _externColor, uint8_t FLAG = 0b0);
	CosmicBody(float _xPos, float _yPos, float _mass, float _radius, Vector2d _speed, glColor _color = { 0.5f, 0.5f, 0.5f }, uint8_t FLAG = 0b0);
	CosmicBody(float _xPos, float _yPos, float _mass, float _radius, Vector2d _speed, glColor _innerColor, glColor _externColor, uint8_t FLAG = 0b0);

	float getXpos();
	float getYpos();
	double getMass();
	float getRadius();
	glColor getInnerColor();
	glColor getExternColor();
	Vector2d getSpeed();
	bool isMoovable();

	void setXpos(float _xpos);
	void setYpos(float _ypos);
	void setMass(float _mass);
	void setRadius(float _radius);
	void setColor(glColor _color);
	void setInnerCoolor(glColor _innerColor);
	void setExternColor(glColor _externColor);
	void setSpeed(Vector2d _speed);
	void setSpeed(float _xspeed, float _yspeed);
	void setMoovable(bool _moovable);

	void proceed();
	void applyForce(Force* _force);
	void applyAcceleration(Vector2d _acceleration)

	~CosmicBody();

private:
	bool m_moovable;
	float m_xPos;
	float m_yPos;
	double m_mass;
	float m_radius;
	glColor m_innerColor;
	glColor m_externColor;
	Vector2d m_speed;
};