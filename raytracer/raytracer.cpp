#include <iostream>
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
		glm::point3 target = rec.p + rec.normal + glm::random_in_hemisphere(rec.normal);
		return 0.5 * ray_color(rtl::ray(rec.p, target - rec.p), world, depth - 1);
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
	world.add(std::make_unique<rtl::sphere>(glm::point3{ 0, 0, -1 }, 0.5));
	world.add(std::make_unique<rtl::sphere>(glm::point3{ 0, -100.5, -1 }, 100));


	rtl::camera cam;

	std::cout << std::format("P3\n{} {}\n255\n", img_width, img_height);
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
			rtl::write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}
