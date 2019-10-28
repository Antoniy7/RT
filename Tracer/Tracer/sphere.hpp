#pragma once
#ifndef SPHEREH
#define SPHEREH

#include"object.hpp"
#include"vec3.hpp"
#include<functional>

class Sphere :public Object {
public:
	Sphere() { ; }
	Sphere(Vec3 c, float r) :center{ c }, radius{ r } {; }
	virtual bool Hit(const Ray&r, float t_min,
		float t_max, HitData& records)const;


	Vec3 center;
	float radius;
};

bool Sphere::Hit(const Ray&r,
	float t_min, float t_max, HitData& records)const {
	Vec3 oc = r.Origin() - center;
	float a = Dot(r.Direction(), r.Direction());
	float b = 2.0 * Dot(oc, r.Direction());
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;

	if (discriminant < 0) {
		return false;
	}
	else if (discriminant > 0) {

		std::function<bool(int)>
			check = [&r, &t_min, &t_max, &records, this](const int& root) {
			if (root<t_max && root>t_min) {
				records.t = root;
				records.point = r.Point_At_Parameter(records.t);
				records.normal = (records.point - center) / radius;
				//records.normal = UnitVector(records.p - center);
				return true;
			}
			return false;
		};

		auto root = (-b - sqrt(discriminant)) / (2.0*a);
		if (check(root))return true;
		else {
			root = (-b + sqrt(discriminant)) / (2.0*a);
			return check(root);
		}

	}
}


#endif
