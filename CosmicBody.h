#pragma once
#include "Vector2d.h"
#include "Force.h"
#include "GravitySim.h"

class CosmicBody {
public:
	CosmicBody();
	CosmicBody(CosmicBody* _cosmicBody);
	CosmicBody(float _xpos, float _ypos, float _mass, float _radius, float _xSpeed = 0.f, float _ySpeed = 0.f, glColor _color = {0.5f, 0.5f, 0.5f});
	CosmicBody(float _xpos, float _ypos, float _mass, float _radius, float _xSpeed, float _ySpeed, glColor _innerColor, glColor _externColor);
	CosmicBody(float _xpos, float _ypos, float _mass, float _radius, Vector2d _speed, glColor _color = {0.5f, 0.5f, 0.5f});
	CosmicBody(float _xpos, float _ypos, float _mass, float _radius, Vector2d _speed, glColor _innerColor, glColor _externColor);

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

	virtual void proceed();
	virtual void applyForce(Force* _force);

	~CosmicBody();

private:
	bool m_moovable = true;
	float m_xpos;
	float m_ypos;
	double m_mass;
	float m_radius;
	glColor m_innerColor;
	glColor m_externColor;
	Vector2d m_speed;
};