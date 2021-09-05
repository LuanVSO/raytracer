#include <iostream>
#include <format>
#include <cmath>

import color;
import vec3;
import ray;

double hit_sphere(const lvs::point3& center, double radius, const lvs::ray& r) {
	using lvs::dot;
	const lvs::vec3 oc = r.origin() - center;
	const auto a{ r.direction().length_squared() };
	const auto half_b{ dot(oc, r.direction()) };
	const auto c{ oc.length_squared() - radius * radius };
	const auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) {
		return -1.;
	}
	else {
		return (-half_b - std::sqrt(discriminant)) / a;
	}
}

lvs::color ray_color(const lvs::ray& r) {
	using lvs::color, lvs::vec3;
	auto t{ hit_sphere({0,0,-1},.5,r) };
	if (t > 0.)
	{
		const auto N{ lvs::unit_vector(r.at(t) - vec3(0,0,-1)) };
		return .5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	const lvs::vec3 unit_direction{ lvs::unit_vector(r.direction()) };
	t = .5 * (unit_direction.y() + 1.);
	return (1. - t) * color(1., 1., 1.) + t * color(.5, .7, 1.);
}

int main()
{
	constexpr auto a_ratio{ 16. / 9. };
	constexpr int img_width{ 400 };
	constexpr int img_height{ static_cast<int>(img_width / a_ratio) };

	constexpr auto view_height{ 2. };
	constexpr auto view_width{ a_ratio * view_height };
	constexpr auto focal_length{ 1. };

	constexpr lvs::point3 origin{ 0,0,0 };
	constexpr lvs::vec3 horizontal{ view_width,0,0 };
	constexpr lvs::vec3 vertical{ 0,view_height,0 };
	constexpr lvs::vec3 lower_l_corner{ origin - horizontal / 2 - vertical / 2 - lvs::vec3(0,0,focal_length) };

	std::cout << std::format("P3\n{} {}\n255\n", img_width, img_height);
	for (int j = img_height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < img_width; i++)
		{
			const auto u{ double(i) / (img_width - 1) };
			const auto v{ double(j) / (img_height - 1) };
			const lvs::ray r(origin, lower_l_corner + u * horizontal + v * vertical - origin);
			const auto pixel_color{ ray_color(r) };
			lvs::write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}
