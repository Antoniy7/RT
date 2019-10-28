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
#include"cone.hpp"


class Utilities {
public:
	static void Main(int& nx, int&ny, int&ns, std::ofstream& my_file) {
		//RandomInSphere();
		std::cout << "begin\n";
		std::cout << "P3\n" << nx << " " << ny << "\n255\n";
		my_file << "P3\n" << nx << " " << ny << "\n255\n";

		const float Kval = 255.99;
		Vec3 lower_left_corner(-2.0, -1.0, -1.0);
		Vec3 horizontal(4.0, 0.0, 0.0);
		Vec3 vertical(0.0, 2.0, 0.0);
		Vec3 origin(0.0, 0.0, 0.0);

		//std::vector<std::shared_ptr<Object>>list{};
		Object * list[3];
		list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
		//list[0] = new Cone(Vec3(0, 0, -1), 0.4);
		//list[1] = new Sphere(Vec3(0, -90, -1), 90);// WORKING
		//list[1] = new Sphere(Vec3(0, -90, -1), 90);
		list[1] = new Sphere(Vec3(0, -101, -1), 101);
		//list[2] = new Cone(Vec3(0.5, 0.5, -1), 0.1);
		Object * world = new ObjectList(list, 2);

		Camera cam;

		//for (int j = 0; j <ny; ++j) {
		for (int j = ny - 1; j > 0; --j) {
			for (int i = 0; i < nx; ++i) {
				Vec3  col(0, 0, 0);
				//auto random = RandomInSphere();
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);

				auto r = cam.GetRay(u, v);
				Vec3 p = r.Point_At_Parameter(2.0);
				col = Color1(r, world);
				//col = SHIBCOLOR(r,world);
				//col = SHIBANCOLolr(r); //WORKING
				//col = SHIBCOLOR_TOFIX_IT(r, world);//trying to the end
				int ir = int(255.99*col[0]);
				int ig = int(255.99*col[1]);
				int ib = int(255.99*col[2]);
				my_file << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	/*static Vec3 SHIBCOLOR(const Ray& r, Object* world) {
		HitData rec;
		if (world->Hit(r, 0.0, FLT_MAX, rec)) {
			return 0.5*Vec3(rec.normal.x() + 1,
				rec.normal.y() + 1,
				rec.normal.z() + 1);
		}
		else {
			Vec3 unit_directon = UnitVector(r.Direction());
			float t = 0.5*(unit_directon.y() + 1.0);
			return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
		}
	}*/
	static Vec3 SHIBCOLOR_TOFIX_IT(const Ray& r, Object* world) {
		HitData rec;
		if (world->Hit(r, 0.0, FLT_MAX, rec)) {

			if (rec.t > 0.0) {
				Vec3 n = UnitVector
					//(r.Point_At_Parameter(rec.t) - Vec3(0, 0, -1));
					(r.Point_At_Parameter(-1.0) - Vec3(0, 0, -1));
					//(rec.point - r.Point_At_Parameter(2.0));
				return 0.5*Vec3(n.x() + 1, n.y() + 1, n.z() + 1);
			}
			else {
				Vec3 unit_directon = UnitVector(r.Direction());
				float t = 0.5*(unit_directon.y() + 1.0);
				return (1.0 - t)*Vec3(0.0, 0.0, 0.0) +
					t * Vec3(0.1, 0.0, 0.10);
			}

		}
		else {
			Vec3 unit_directon = UnitVector(r.Direction());
			float t = 0.5*(unit_directon.y() + 1.0);
			return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
		}
	}
	static Vec3 SHIBANCOLolr(Ray r) {
		Sphere x = Sphere(Vec3(0, 0, -1), 0.5);
		//float t = HitSphere(Vec3(0, 0, -1), 0.5, r);
		float t = HitSphere(x.center, x.radius, r);
		if (t > 0.0) {
			Vec3 n = UnitVector(r.Point_At_Parameter(t) - Vec3(0, 0, -1));
			return 0.5*Vec3(n.x() + 1, n.y() + 1, n.z() + 1);
		}
		Vec3 unit_directon = UnitVector(r.Direction());
		t = 0.5*(unit_directon.y() + 1.0);
		return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}

	static float HitSphere(const Vec3& center, float radius, Ray&r) {
		Vec3 oc = r.Origin() - center;
		float a = Dot(r.Direction(), r.Direction());
		float b = Dot(oc, r.Direction());
		float c = Dot(oc, oc) - radius * radius;
		float discriminant = b * b - a * c;
		if (discriminant < 0)return -1.0;
		else
			return (-b - sqrt(discriminant)) / (a);

	}



	static Vec3 Color1(const Ray&r, Object* world) {
		HitData data;
		if (world->Hit(r, 0.0, FLT_MAX, data)) {
			return 0.5*Vec3(data.normal.x() + 1,
				data.normal.y() + 1,
				data.normal.z() + 1);
		}
		else {
			Vec3 unit_direction = UnitVector(r.Direction());
			float t = 0.5*(unit_direction.y() + 1);
			return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
		}
	}

	static Vec3 Color(const Ray&r, Object*world) {
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
		/*while (true) {
			if (Dot(point, point) >= 1.0) break;
			auto data = RandomInSphere();
			point = 2.0 *
				Vec3(data.x(), data.y(), data.z()) -
				Vec3(1, 1, 1);
		}*/
		do {
			auto data = RandomInSphere();
			point =
				2.0*Vec3(data.x(), data.y(), data.z())
				- Vec3(1, 1, 1);
		} while (Dot(point, point) >= 1);
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

