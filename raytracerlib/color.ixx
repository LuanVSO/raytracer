module;
#include <iostream>
#include <algorithm>
#include <cmath>
export module raytracerlib.color;
import raytracerlib.vec3;

export void write_color(std::ostream& os, const color& pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples and gamma-correct for gamma=2.0.
	const auto scale{ 1. / samples_per_pixel };
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);

	os << static_cast<int>(256. * std::clamp(r, 0., 0.999999999999999)) << ' '
		<< static_cast<int>(256. * std::clamp(g, 0., 0.999999999999999)) << ' '
		<< static_cast<int>(256. * std::clamp(b, 0., 0.999999999999999)) << '\n';
}
