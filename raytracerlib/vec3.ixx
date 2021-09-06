module;
#include <cmath>
#include <iostream>
#include <cstdint>
#include <concepts>
#include <cassert>
export module raytracerlib.vec3;
using std::sqrt;
export {
	class vec3 {
		double e[3];
	public:
		constexpr vec3() noexcept :e{ 0,0,0 } {}
		constexpr vec3(double e0, double e1, double e2) noexcept : e{ e0,e1,e2 } {}

		constexpr const inline double x() const noexcept { return e[0]; }
		constexpr const inline double y() const noexcept { return e[1]; }
		constexpr const inline double z() const noexcept { return e[2]; }

		constexpr vec3 operator-() const noexcept { return vec3(-e[0], -e[1], -e[2]); }
		constexpr const inline double operator[](uint8_t i) const noexcept { assert(i < 3); return e[i]; }
		constexpr inline double& operator[](uint8_t i) noexcept { assert(i < 3); return e[i]; }

		constexpr inline vec3& operator+=(const vec3& v) noexcept {
			e[0] += v[0];
			e[1] += v[1];
			e[2] += v[2];
			return *this;
		}

		constexpr inline vec3& operator*=(const double t) noexcept {
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		constexpr inline vec3& operator/=(const double t) noexcept {
			return *this *= 1 / t;
		}

		constexpr const inline double lenght_squared() const noexcept {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}
		double const lenght() const {
			return sqrt(lenght_squared());
		}
	};
	using point3 = vec3; // 3D point
	using color = vec3;// RGB Color

	inline std::ostream& operator<<(std::ostream& os, const  vec3& v) {
		return os << v[0] << ' ' << v[1] << ' ' << v[2];
	}

	constexpr inline vec3 operator+(const vec3& u, const vec3& v) noexcept {
		return { u[0] + v[0],u[1] + v[1] ,u[2] + v[2] };
	}

	constexpr inline vec3 operator-(const vec3& u, const vec3& v) noexcept {
		return { u[0] - v[0] ,u[1] - v[1] ,u[2] - v[2] };
	}

	constexpr inline vec3 operator*(const vec3& u, const vec3& v) noexcept {
		return { u[0] * v[0] ,u[1] * v[1] ,u[2] * v[2] };
	}

	constexpr inline vec3 operator*(double t, const vec3& v) noexcept {
		return { t * v[0] ,t * v[1] ,t * v[2] };
	}

	constexpr inline vec3 operator*(const vec3& v, double t) noexcept {
		return t * v;
	}

	constexpr inline vec3 operator/(const vec3& v, double t) noexcept {
		return (1 / t) * v;
	}

	constexpr inline double dot(const vec3& u, const vec3& v) noexcept {
		return u[0] * v[0]
			+ u[1] * v[1]
			+ u[2] * v[2];
	}

	constexpr inline vec3 cross(const vec3& u, const vec3& v) noexcept {
		return { u[1] * v[2] - u[2] * v[1],
				u[2] * v[0] - u[0] * v[2],
				u[0] * v[1] - u[1] * v[0] };
	}

	inline vec3 unit_vector(const vec3& v) noexcept {
		return v / v.lenght();
	}
}