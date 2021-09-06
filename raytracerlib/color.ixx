module;
#include <iostream>
#include <algorithm>
export module raytracerlib.color;
import raytracerlib.vec3;

export void write_color(std::ostream& os, const color& pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	const auto scale{ 1. / samples_per_pixel };
	r *= scale;
	g *= scale;
	b *= scale;

	os << static_cast<int>(256. * std::clamp(r, 0., 0.999999999999999)) << ' '
		<< static_cast<int>(256. * std::clamp(g, 0., 0.999999999999999)) << ' '
		<< static_cast<int>(256. * std::clamp(b, 0., 0.999999999999999)) << '\n';
}
