#pragma once

#include"object.hpp"
#include<memory>
#include<vector>

class ObjectList : public Object {
public:
	ObjectList() { ; }
	ObjectList(std::vector<std::shared_ptr<Object>> l) {
		l_list = l;
	}
	virtual bool Hit(const Ray&r,
		float t_min, float t_max, HitData&records)const;

	std::vector<std::shared_ptr<Object>>l_list;
};

bool ObjectList::Hit(const Ray&r,
	float t_min, float t_max, HitData&records)const {
	HitData data;
	bool hit_anything = false;
	float closest_so_fat = t_max;

	for (int i = 0; i < l_list.size(); ++i) {
		if (l_list.at(i)->
			Hit(r, t_min, closest_so_fat, data)) {
			hit_anything = true;
			closest_so_fat = data.t;
			records = data;
		}
	}
	return hit_anything;
}