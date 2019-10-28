#pragma once
#include"ray.hpp"

class Camera {
public:
	Camera() {
		lower_left_corner = Vec3(-2.0, -1.0, -1.0);
		horizontal = Vec3(4.0, 0.0, 0.0);
		vertical = Vec3(0.0, 2.0, 0.0);
		origin = Vec3(0.0, 0.0, 0.0);
	}
	Ray GetRay(float u, float v) {
		return Ray(origin,
			UnitVector(lower_left_corner +
			((horizontal*u) + (vertical*v))));
	}

private:
	Vec3 vertical;
	Vec3 origin;
	Vec3 horizontal;
	Vec3 lower_left_corner;
};

