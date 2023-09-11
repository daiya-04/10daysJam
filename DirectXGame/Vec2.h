#pragma once
#include <cmath>
#include <algorithm>

class Vec2 {
public:
    float x = 0.0f;
    float y = 0.0f;
public:
    inline Vec2(){}
	inline Vec2(float x,float y) : x(x), y(y){}
	inline Vec2(const Vec2& vector) : x(vector.x), y(vector.y){}

	inline Vec2 operator-() const { return {-x,-y}; }

	inline Vec2& operator+=(const Vec2& vector){
		x += vector.x;
		y += vector.y;
		return *this;
	}

	inline Vec2& operator-=(const Vec2& vector){
		x -= vector.x;
		y -= vector.y;
		return *this;
	}

	inline Vec2& operator*=(const float scalar){
		x *= scalar;
		y *= scalar;
		return *this;
	}

	inline Vec2& operator/=(const float scalar){
		x /= scalar;
		y /= scalar;
		return *this;
	}

	friend inline Vec2 operator+(const Vec2& v1,const Vec2& v2){
		return { v1.x + v2.x, v1.y + v2.y };
	}

	friend inline Vec2 operator-(const Vec2& v1,const Vec2& v2){
		return { v1.x - v2.x, v1.y - v2.y };
	}

	friend inline Vec2 operator*(float scalar,const Vec2& vector){
		return { scalar * vector.x, scalar * vector.y };
	}

	friend inline Vec2 operator*(const Vec2& vector, float scalar){
		return scalar * vector;
	}

	friend inline Vec2 operator/(const Vec2& vector, float scalar){
		return { vector.x / scalar, vector.y / scalar };
	}

	friend inline bool operator==(const Vec2& v1,const Vec2& v2){
		return { v1.x == v2.x && v1.y == v2.y};
	}

	friend inline bool operator!=(const Vec2& v1,const Vec2& v2){
		return !(v1 == v2);
	}

	friend inline float Dot(const Vec2& v1,const Vec2& v2){
		return v1.x * v2.x + v1.y * v2.y;
	}

	friend inline float Cross(const Vec2& v1,const Vec2& v2){
		return v1.x * v2.y - v1.y * v2.x;
	}

	inline float Length() const {
		return std::sqrtf(x * x + y * y);
	}

	inline Vec2 Normalize() const {
		return *this / Length();
	}

	inline Vec2 Normal() const {
		return { -y, x };
	}

	inline Vec2 NegNormal() const {
		return { y, -x };
	}

	friend inline Vec2 Lerp(float t, const Vec2& start, const Vec2& end){
		t = std::clamp(t, 0.0f, 1.0f);
		return { (1.0f - t) * start + t * end };
	}

	friend inline Vec2 Bezier(const Vec2& p0, const Vec2& p1, const Vec2& p2, float t){
		Vec2 p0p1 = Lerp(t, p0, p1);
		Vec2 p1p2 = Lerp(t, p1, p2);
		Vec2 p = Lerp(t, p0p1, p1p2);

		return p;
	}
};