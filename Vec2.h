#pragma once
#include <cmath>
#include <iostream>
#include <string>

struct Vector2 {
	float x, y;

	static const Vector2 Zero, One;

	// Constructor to initialize x and y
	Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

	inline void operator+=(Vector2& right) {
		x += right.x;
		y += right.y;
	}
	inline void operator-=(Vector2& right) {
		x -= right.x;
		y -= right.y;
	}

	inline void operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
	}

	inline void operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
	}

	friend Vector2 operator+(Vector2& left, Vector2& right) {
		return { left.x - right.x, left.y - right.y };
	}

	friend Vector2 operator*(Vector2& left, float scalar) {
		return { left.x * scalar, left.y * scalar };
	}

	friend Vector2 operator*(float scalar, Vector2& right) {
		return { scalar * right.x, scalar * right.y };
	}

	friend Vector2 operator/(Vector2& left, float scalar) {
		return { left.x / scalar, left.y / scalar };
	}

	bool operator!=(const Vector2& other) const
	{
		return x != other.x || y != other.y;
	}

	inline float GetMagnitude(){
		return sqrt(x * x + y * y);
	}

	friend float Dot(Vector2& left, Vector2& right) {
		return left.x * right.x + left.y * right.y;

	}

	inline float Normalize() {
		(*this) /= GetMagnitude();
	}

	inline Vector2 Normalized() {
		return (*this) / GetMagnitude();
	}

	inline std::string ToString() {
		return "( " + std::to_string(x) + " , " + std::to_string(y) + " ) ";
	}

};


