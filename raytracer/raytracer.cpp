#include <iostream>
#include <format>
#include <memory>
#include <cmath>

import raytracerlib;
import raytracerlib.camera;

color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return .5 * (rec.normal + color{ 1,1,1 });
	}
	const vec3 unit_direction{ unit_vector(r.direction()) };
	const auto t{ .5 * (unit_direction.y() + 1.0) };
	return (1. - t) * color { 1., 1., 1. } + t * color{ .5,.7,1. };
}

int main()
{
	constexpr auto a_ratio{ 16. / 9. };
	constexpr int img_width{ 400 };
	constexpr int img_height{ static_cast<int>(img_width / a_ratio) };
	constexpr auto samples_per_pixel{ 100 };

	hittable_list world;
	world.add(std::make_unique<sphere>(point3{ 0, 0, -1 }, 0.5));
	world.add(std::make_unique<sphere>(point3{ 0, -100.5, -1 }, 100));


	constexpr auto view_height{ 2. };
	constexpr auto view_width{ a_ratio * view_height };
	constexpr auto focal_length{ 1. };

	camera cam;

	std::cout << std::format("P3\n{} {}\n255\n", img_width, img_height);
	for (int j = img_height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i != img_width; i++)
		{
			color pixel_color{ 0, 0, 0 };
			for (int s{}; s != samples_per_pixel; ++s) {
				const auto u{ (i + random_canonical()) / (img_width - 1) };
				const auto v{ (j + random_canonical()) / (img_height - 1) };
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}
