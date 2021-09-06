export module raytracerlib.ray;
import raytracerlib.vec3;
export {
	class ray {
	public:
		constexpr ray() {}
		constexpr ray(const point3& origin, const vec3& direction) : orig{ origin }, dir{ direction } {}

		constexpr point3 origin() const { return orig; }
		constexpr vec3 direction() const { return dir; }

		constexpr point3 at(double t) const {
			return orig + t * dir;
		}
	private:
		point3 orig;
		vec3 dir;
	};

}