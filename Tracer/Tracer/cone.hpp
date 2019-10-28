#pragma once

#include"object.hpp"
#include"vec3.hpp"
#include<functional>

class Cone :public Object {
public:
	Cone() { ; }
	Cone(Vec3 c, float r) :center{ c }, radius{ r } {; }
	virtual bool Hit(const Ray&r, float t_min,
		float t_max, HitData& records)const;


	Vec3 center;
	float radius;
};

bool Cone::Hit(const Ray&r,
	float t_min, float t_max, HitData& records)const {
	Vec3 oc = r.Origin() - center;
	float a = Dot(r.Direction(), r.Direction());
	float b = Dot(oc, r.Direction());
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	bool negative_root = false;
	if (discriminant < 0) {
		return false;
	}
	else if (discriminant > 0) {

		std::function<bool(int)>
			check = [&r, &t_min, &t_max,
			&records, this, &negative_root](const float& root) {
			if (root<t_max && root>t_min) {
				if (!negative_root) {
					records.t = root;
					records.point = r.Point_At_Parameter(records.t);
					records.normal = UnitVector((records.point - center));
					negative_root = true;
				}
				return true;
			}
			return false;
		};

		//float root = (-b - std::sqrt(discriminant)) / (a);
		float root = (-b + std::sqrt(discriminant)) / (a);
		if (check(root))return true;
		//return false;
		else {
			root = (-b - std::sqrt(discriminant)) / (a);
			return check(root);
		}

	}
}
