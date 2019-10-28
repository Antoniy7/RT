#pragma once

#include"object.hpp"
#include<memory>
#include<vector>

class ObjectList : public Object {
public:
	ObjectList() { ; }
	ObjectList(Object** l, int n) {
		size = n;
		list = l;
	}
	virtual bool Hit(const Ray&r,
		float t_min, float t_max, HitData&records)const;

	//std::vector<std::shared_ptr<Object>>l_list;
	Object** list;
	int size;
};

bool ObjectList::Hit(const Ray&r,
	float t_min, float t_max, HitData&records)const {
	HitData data;
	bool hit_anything = false;
	double closest_so_fat = t_max;

	for (int i = 0; i < size; ++i) {
		if (list[i]->
			Hit(r, t_min, closest_so_fat, data)) {
			hit_anything = true;
			closest_so_fat = data.t;
			records = data;
		}
	}
	return hit_anything;
}