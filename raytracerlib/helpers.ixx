module;
#include <numbers>
#include <cmath>
#include <limits>
#include <random>
export module raytracerlib.helpers;
import  glm.vec3;


export constexpr auto infinity = std::numeric_limits<double>::infinity();


export inline double random_canonical() {
	return glm::linearRand(0.,1.);
}


export constexpr inline double degrees_to_radians(double degrees) {
	return degrees * std::numbers::pi / 180.;
}

