module;
#include <ostream>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/gtc/random.hpp>
export module glm.vec3;

export namespace glm {
	using color = dvec3;
	using point3 = dvec3;
	// fixme: was getting multiple operators * when exporting importing the header
	using glm::dvec3;
	using glm::cross;
	using glm::dot;
	using glm::normalize;
	using glm::linearRand;

	using glm::operator%, glm::operator*, glm::operator+, glm::operator-, glm::operator/,
		glm::operator&, glm::operator&&, glm::operator<<, glm::operator==, glm::operator>>,
		glm::operator^, glm::operator|, glm::operator||,glm::operator!=,glm::operator~;

	double legth_squared(const glm::dvec3& a) {
		return a.x * a.x + a.y * a.y + a.z * a.z;
	}

	std::ostream& operator <<(std::ostream& os, glm::dvec3& a) {
		return os << a.x << ' ' << a.y << ' ' << a.z;
	}

	dvec3 random_unit_vector() {
		return normalize(glm::ballRand(1.));
	}
	dvec3 random_in_hemisphere(const dvec3& normal) {
		const dvec3 in_unit_sphere{ glm::ballRand(1.) };
		if (dot(in_unit_sphere, normal) > 0.)
		{
			return in_unit_sphere;
		}
		return -in_unit_sphere;
	}
}