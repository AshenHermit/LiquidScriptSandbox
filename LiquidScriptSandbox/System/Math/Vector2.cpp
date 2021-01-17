#include "Vector2.h"
Vector2::Vector2() {

}

Vector2::Vector2(float _x) {
	x = _x;
	y = _x;
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2& Vector2::operator+=(Vector2 right)
{
	x += right.x;
	y += right.y;
	return *this;
}

Vector2 Vector2::operator+(Vector2 right) {
	return Vector2(x, y) += right;
}

Vector2& Vector2::operator-=(Vector2 right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vector2 Vector2::operator-(Vector2 right)
{
	return Vector2(x, y) -= right;
}

Vector2& Vector2::operator*=(Vector2 right)
{
	x *= right.x;
	y *= right.y;
	return *this;
}

Vector2 Vector2::operator*(Vector2 right)
{
	return Vector2(x, y) *= right;
}

Vector2& Vector2::operator*=(float right)
{
	x *= right;
	y *= right;
	return *this;
}

Vector2 Vector2::operator*(float right)
{
	return Vector2(x, y) *= right;
}

Vector2& Vector2::operator/=(Vector2 right)
{
	x /= right.x;
	y /= right.y;
	return *this;
}

Vector2& Vector2::operator/=(float right)
{
	x /= right;
	y /= right;
	return *this;
}

Vector2 Vector2::operator/(Vector2 right)
{
	return Vector2(x, y) /= right;
}

Vector2 Vector2::operator/(float right)
{
	return Vector2(x, y) /= right;
}

Vector2 Vector2::Mul(float right)
{
	return *this * (right);
}

Vector2 Vector2::Div(float right)
{
	return *this / (right);
}
