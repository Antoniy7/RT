#include<iostream>
#include<algorithm>
#include<set>
#include<fstream>
#include"vec3.hpp"
#include "ray.hpp"
#include"sphere.hpp"
#include"Object_List.hpp"
#include <random>
#include"camera.hpp"


class Utilities {
public:
	static void Main(int& nx, int&ny, int&ns, std::ofstream& my_file) {
		RandomInSphere();
		std::cout << "begin\n";
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
		Camera cam;

		//for (int j = 0; j <ny; ++j) {
		for (int j = ny - 1; j > 0; --j) {
			for (int i = 0; i < nx; ++i) {
				Vec3  col;
				for (int s = 0; s < ns; ++s) {
					float u = static_cast<float>(i) / static_cast<float>(nx);
					float v = static_cast<float>(j) / static_cast<float>(ny);

					auto r = cam.GetRay(u, v);
					col += Color(r, world);
					//Vec3 col{ 1,1,1 };
				}
			col/=ns;
				int ir = static_cast<int>(Kval*std::sqrt(col[0]));
				int ig = static_cast<int>(Kval*std::sqrt(col[1]));
				int ib = static_cast<int>(Kval*std::sqrt(col[2]));
				my_file << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	static Vec3 Color(const Ray&r, std::unique_ptr<Object>&world) {
		HitData record;
		if (world->Hit(r, 0.0, FLT_MAX, record)) {
			Vec3 target =
				record.point +
				record.normal +
				GenerateRandomInSphere();
			Ray new_ray(record.point, target - record.point);
			return 0.5*Color(new_ray, world);
		}
		Vec3 unit_direction = UnitVector(r.Direction());
		float t = 0.5* (unit_direction.y() + 1.0);
		return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}

	static Vec3 GenerateRandomInSphere() {
		Vec3 point;
		while (true) {
			if (Dot(point, point) >= 1.0) break;
			auto data = RandomInSphere();
			point = 2.0 *
				Vec3(data.x(), data.y(), data.z()) -
				Vec3(1, 1, 1);
		}
		return point;
	}

	static Vec3 RandomInSphere() {
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_real_distribution<float>randData(0, 1);
		auto x = randData(rng);
		auto y = randData(rng);
		auto z = randData(rng);

		return Vec3{ x,y,z };
	}

};

int main() {
	std::ofstream myfile;
	myfile.open("test.ppm");
	int nx = 200;
	int ny = 100;
	int ns = 100;
	Utilities::Main(nx, ny, ns, myfile);


	//system("pause");
	return 0;
}

