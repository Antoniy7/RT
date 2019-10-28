#pragma once
#ifndef RAYH
#define RAYH
#include"vec3.hpp"

class Ray {
public:
	Ray() {}
	Ray(const Vec3&a, const Vec3&b) { A = a; B = b; }
	Vec3 Origin()const { return A; }
	Vec3 Direction() const { return B; }
	Vec3 Point_At_Parameter(float t)const {
		Vec3 tB(B.x()*t, B.y()*t, B.z()*t);
		return A+tB;
	}

	//private:
	Vec3 A;
	Vec3 B;
};


#endif