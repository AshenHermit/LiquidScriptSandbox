#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float _x);
	Vector2(float _x, float _y);

	float x = 0;
	float y = 0;

	Vector2& operator+=(Vector2 right);
	Vector2 operator+(Vector2 right);

	Vector2& operator-=(Vector2 right);
	Vector2 operator-(Vector2 right);

	Vector2& operator*=(Vector2 right);
	Vector2 operator*(Vector2 right);
	Vector2& operator*=(float right);
	Vector2 operator*(float right);

	Vector2& operator/=(Vector2 right);
	Vector2 operator/(Vector2 right);
	Vector2& operator/=(float right);
	Vector2 operator/(float right);

	Vector2 Mul(float right);
	Vector2 Div(float right);
};

