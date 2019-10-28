#pragma once
#ifndef OBJECTH
#define OBJECTH

#include"ray.hpp"

struct HitData {
	Vec3 point;
	Vec3 normal;
	float t;
};

class Object {
public:
	virtual bool Hit(
		const Ray&r,
		float t_min, 
		float t_max, 
		HitData& rec)const = 0;
};


#endif