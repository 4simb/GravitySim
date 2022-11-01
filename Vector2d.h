#pragma once

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

protected:
	float m_x;
	float m_y;
};
