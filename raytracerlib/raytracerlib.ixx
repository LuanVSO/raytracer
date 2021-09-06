module;
#include <numbers>
#include <cmath>
#include <limits>
#include <random>
export module raytracerlib;
export import raytracerlib.vec3;
export import raytracerlib.color;
export import raytracerlib.ray;
export import raytracerlib.hittable;
export import raytracerlib.sphere;
export import raytracerlib.hittable_list;

export constexpr auto infinity = std::numeric_limits<double>::infinity();

static std::random_device rd;
export std::mt19937_64 rand_gen(rd());

export inline double random_canonical() {
	return std::generate_canonical<double, 1>(rand_gen);
}

export inline double random_double(double min, double max) {
	std::uniform_real_distribution<double> dis(min, max);
	return dis(rand_gen);
}

export constexpr inline double degrees_to_radians(double degrees) {
	return degrees * std::numbers::pi / 180.;
}

