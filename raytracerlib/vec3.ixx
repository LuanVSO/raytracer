module;
#include <cmath>
#include <iostream>
#include <cstdint>
#include <concepts>
#include <cassert>
export module vec3;
using std::sqrt;
export {
	class vec3 {
		double e[3];
	public:
		constexpr vec3() :e{ 0,0,0 } {}
		constexpr vec3(double e0, double e1, double e2) : e{ e0,e1,e2 } {}

		constexpr const inline double x() const { return e[0]; }
		constexpr const inline double y() const { return e[1]; }
		constexpr const inline double z() const { return e[2]; }

		constexpr const vec3 operator~() const { return vec3(-e[0], -e[1], -e[2]); }
		constexpr const inline double operator[](uint8_t i) const { assert(i < 3); return e[i]; }
		constexpr inline double& operator[](uint8_t i) { assert(i < 3); return e[i]; }

		constexpr vec3& operator+=(const vec3& v) {
			e[0] += v[0];
			e[1] += v[1];
			e[2] += v[2];
			return *this;
		}

		constexpr vec3& operator*=(const double t) {
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		constexpr vec3& operator/=(const double t) {
			return *this *= 1 / t;
		}

		constexpr const double length_squared() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}
		double const lenght() const {
			return sqrt(length_squared());
		}
	};
	typedef vec3 point3;// 3D point
	typedef vec3 color;// RGB Color

	template<typename T>
	concept vec = std::same_as<T, vec3> || std::same_as<T, point3> || std::same_as<T, color>;

	inline std::ostream& operator<<(std::ostream& os, const vec auto& v) {
		return os << v[0] << ' ' << v[1] << ' ' << v[2];
	}

	template<vec V>
	constexpr inline V operator+(const V& u, const V& v) {
		return { u[0] + v[0],u[1] + v[1] ,u[2] + v[2] };
	}

	template <vec V>
	constexpr inline V operator-(const V& u, const V& v) {
		return { u[0] - v[0] ,u[1] - v[1] ,u[2] - v[2] };
	}

	template <vec V>
	constexpr inline V operator*(const V& u, const V& v) {
		return { u[0] * v[0] ,u[1] * v[1] ,u[2] * v[2] };
	}

	template <vec V>
	constexpr inline V operator*(double t, const V& v) {
		return { t * v[0] ,t * v[1] ,t * v[2] };
	}

	template <vec V>
	constexpr inline V operator*(const V& v, double t) {
		return t * v;
	}

	template <vec V>
	constexpr inline V operator/(const V& v, double t) {
		return (1 / t) * v;
	}

	template <vec V>
	constexpr inline double dot(const V& u, const V& v) {
		return u[0] * v[0]
			+ u[1] * v[1]
			+ u[2] * v[2];
	}

	template <vec V>
	constexpr inline V cross(const V& u, const V& v) {
		return { u[1] * v[2] - u[2] * v[1],
				u[2] * v[0] - u[0] * v[2],
				u[0] * v[1] - u[1] * v[0] };
	}

	template<vec V>
	inline V unit_vector(const V& v) {
		return v / v.lenght();
	}
}