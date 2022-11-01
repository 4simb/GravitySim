#pragma once

struct glColor {
	float m_red;
	float m_green;
	float m_blue;
	float m_alpha = 1.f;
};

class Vector2d {
public:
	Vector2d();
	Vector2d(float _x, float _y);
	Vector2d(Vector2d* _vector);

	float getX();
	float getY();
	float module();
	virtual void normalize();

	void setX(float _x);
	void setY(float _y);

	~Vector2d();

private:
	float m_x;
	float m_y;
};

class Force : Vector2d {
public:
	Force(Vector2d* _vector, float _value);
	Force(float _x, float _y, float _value);
	Force(Force* _force);

	void normalize(); // normalized * value

	~Force();
private:
	float m_value; // in Newtons
};

class CosmicBody {
public:
	CosmicBody();
	~CosmicBody();

	int getMass();
	int getRadius();
	glColor getColor();
	Vector2d getSpeed();

	void applyForce(Force _force);

private:
	float m_mass;
	float m_radius;

	Vector2d m_speed;
};
