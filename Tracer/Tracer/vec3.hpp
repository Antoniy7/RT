#ifndef VEC3H
#define VEC3H

#include<math.h>
#include<iostream>
#include<stdlib.h>

class Vec3 {
public:
	Vec3() {}
	Vec3(float e0, float e1, float e2) {
		elem[0] = e0;
		elem[1] = e1;
		elem[2] = e2;
	}
	inline float x()const { return elem[0]; }
	inline float y()const { return elem[1]; }
	inline float z()const { return elem[2]; }
	inline float r() { return elem[0]; }
	inline float g() { return elem[1]; }
	inline float b() { return elem[2]; }

	inline const Vec3& operator+()const { return *this; }
	inline Vec3 operator-()const { return Vec3(-elem[0], -elem[1], -elem[2]); }
	inline float operator [] (int index)const { return elem[index]; }
	inline float& operator[](int index) { return elem[index]; }

	inline Vec3& operator+=(const Vec3& v);
	inline Vec3& operator-=(const Vec3& v);
	inline Vec3& operator*=(const Vec3& v);
	inline Vec3& operator/=(const Vec3& v);

	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);

	inline float Length()const {
		return sqrt(
			elem[0] * elem[0] +
			elem[1] * elem[1] +
			elem[2] * elem[2]
		);
	}
	inline float SquaredLenght()const {
		return
			elem[0] * elem[0] +
			elem[1] * elem[1] +
			elem[2] * elem[2];
	}

	inline void make_unit_vector();

	float elem[3];

};

bool operator<(Vec3 left, Vec3 right)
{	
	return left.x() < right.x();
}

inline Vec3 operator+ (const Vec3 &v1, const Vec3 &v2) {
	//auto xx = v1.x(); const bez const :) 
	//auto yy = v1.r();
	//const float a = v1.r();
	return Vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
inline Vec3 operator- (const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

//are for colors 
inline Vec3 operator* (const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.x() * v2.x(), v1.y() *v2.y(), v1.z() * v2.z());
}
inline Vec3 operator/ (const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}
//some geometric operations
inline float Dot(const Vec3 &v1, const Vec3& v2) {
	return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
}

inline Vec3 Cross(const Vec3 &v1, const Vec3 &v2) {
	return Vec3((v1.y()*v2.z() - v1.z()*v2.y()),
		(-(v1.x()*v2.z() - v1.z()*v2.x())),
		(v1.x()*v2.y() - v1.y()*v2.x()));
}
inline Vec3 UnitVector(Vec3 v) {
	float len = v.Length();
	return Vec3(
		v.x() / len,
		v.y() / len,
		v.z() / len);
}

inline Vec3 operator*(Vec3 v, float t) {
	return Vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline Vec3 operator/(Vec3 v, float t) {
	return Vec3(v[0] / t, v[1] / t, v[2] / t);
}

inline Vec3 operator*(float t, Vec3 v) {
	return Vec3(v[0] * t, v[1] * t, v[2] * t);
}


#endif