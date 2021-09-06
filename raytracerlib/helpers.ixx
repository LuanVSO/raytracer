module;
#include <numbers>
#include <cmath>
#include <limits>
#include <random>
export module raytracerlib.helpers;


export constexpr auto infinity = std::numeric_limits<double>::infinity();


export inline double random_canonical() {
	std::random_device rd;
	static std::mt19937_64 rand_gen(rd());
	return std::generate_canonical<double, 1>(rand_gen);
}

export inline double random_double(double min, double max) {
	std::random_device rd;
	static std::mt19937_64 rand_gen(rd());
	std::uniform_real_distribution<double> dis(min, max);
	return dis(rand_gen);
}

export constexpr inline double degrees_to_radians(double degrees) {
	return degrees * std::numbers::pi / 180.;
}

