#pragma once
#include "Vector2d.h"

class Force : public Vector2d {
public:
	Force(Vector2d* _vector, float _value);
	Force(float _x, float _y, float _value);
	Force(Force* _force);

	void normalize(); // normalized * value

	~Force();
protected:
	float m_value; // Newtons
};
