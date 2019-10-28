#include<iostream>
#include<algorithm>
#include<set>
#include<fstream>
#include"vec3.hpp"
#include "ray.hpp"
#include"sphere.hpp"
#include"Object_List.hpp"

float HitSphere(const Vec3& center, float radius, const Ray&r) {
	Vec3 oc = r.Origin() - center;
	float a = Dot(r.Direction(), r.Direction());
	float b = 2.0 * Dot(oc, r.Direction());
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;

	if (discriminant < 0) { return -1.0; }
	else {
		auto x = (-b + sqrt(discriminant)) / (2.0*a);;
		return (-b - sqrt(discriminant)) / (2.0*a);
	}

}

class Utilities {
public:
	static void Main(int& nx, int&ny, std::ofstream& my_file) {
		std::cout << "P3\n" << nx << " " << ny << "\n255\n";
		my_file << "P3\n" << nx << " " << ny << "\n255\n";

		const float Kval = 255.99;
		Vec3 lower_left_corner(-2.0, -1.0, -1.0);
		Vec3 horizontal(4.0, 0.0, 0.0);
		Vec3 vertical(0.0, 2.0, 0.0);
		Vec3 origin(0.0, 0.0, 0.0);

		std::vector<std::shared_ptr<Object>>list{};
		list.emplace_back(std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5));
		list.emplace_back(std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100));
		std::unique_ptr<Object>world{ std::make_unique<ObjectList>(
			std::move(list)) };
		//FillWorld(list);

		//for (int j = 0; j <ny; ++j) {
		for (int j = ny - 1; j > 0; --j) {
			for (int i = 0; i < nx; ++i) {


				float u = static_cast<float>(i) / static_cast<float>(nx);
				float v = static_cast<float>(j) / static_cast<float>(ny);

				Ray r
				(origin,
					UnitVector
					(lower_left_corner +
					((horizontal*u) + (vertical*v))));

				Vec3 col = Color(r, world);
				//Vec3 col{ 1,1,1 };
				int ir = static_cast<int>(Kval*col[0]);
				int ig = static_cast<int>(Kval*col[1]);
				int ib = static_cast<int>(Kval*col[2]);
				my_file << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	static Vec3 Color(const Ray&r, std::unique_ptr<Object>&world) {
		HitData record;
		if (world->Hit(r, 0.0, FLT_MAX, record)) {
			return 0.5*Vec3(
				record.normal.x() + 1,
				record.normal.y() + 1,
				record.normal.z() + 1);
		}
		Vec3 unit_direction = UnitVector(r.Direction());
		float t = 0.5* (unit_direction.y() + 1.0);
		return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
};

int main() {
	std::ofstream myfile;
	myfile.open("test.ppm");
	int nx = 200;
	int ny = 100;
	Utilities::Main(nx, ny, myfile);


	//system("pause");
	return 0;
}


























