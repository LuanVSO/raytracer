#include <iostream>
#include <fstream>
#include <ios>
#include <format>
#include <memory>
#include <cmath>

import raytracerlib;

glm::color ray_color(const rtl::ray& r, const rtl::hittable& world, int depth) {
	rtl::hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return {};

	if (world.hit(r, 0.00001, infinity, rec)) {
		rtl::ray scattered;
		glm::color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		return { 0,0,0 };
	}

	glm::dvec3 unit_direction = glm::normalize(r.direction());
	auto t = 0.5 * (unit_direction.y + 1.0);
	return (1.0 - t) * glm::color(1.0, 1.0, 1.0) + t * glm::color(0.5, 0.7, 1.0);
}

int main()
{
	constexpr auto a_ratio{ 16. / 9. };
	constexpr int img_width{ 400 };
	constexpr int img_height{ static_cast<int>(img_width / a_ratio) };
	constexpr auto samples_per_pixel{ 100 };
	constexpr auto max_depth{ 50 };

	rtl::hittable_list world;
	auto material_ground = std::make_shared<rtl::lambertian>(glm::color(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<rtl::lambertian>(glm::color(0.7, 0.3, 0.3));
	auto material_left = std::make_shared<rtl::metal>(glm::color(0.8, 0.8, 0.8),0.3);
	auto material_right = std::make_shared<rtl::metal>(glm::color(0.8, 0.6, 0.2),1.0);

	world.add(make_unique<rtl::sphere>(glm::point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_unique<rtl::sphere>(glm::point3(0.0, 0.5, -1.0), 0.5, material_center));
	world.add(make_unique<rtl::sphere>(glm::point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_unique<rtl::sphere>(glm::point3(1.0, 0.0, -1.0), 0.5, material_right));

	rtl::camera cam;

	std::ofstream file;
	file.open("./render.ppm", std::ios::out | std::ios::trunc);

	file << std::format("P3\n{} {}\n255\n", img_width, img_height);
	for (int j = img_height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i != img_width; i++)
		{
			glm::color pixel_color{ 0, 0, 0 };
			for (int s{}; s != samples_per_pixel; ++s) {
				const auto u{ (i + random_canonical()) / (img_width - 1) };
				const auto v{ (j + random_canonical()) / (img_height - 1) };
				rtl::ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			rtl::write_color(file, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
	file.close();
}
