export module raytracerlib.ray;
import glm.vec3;
export namespace rtl {
	class ray {
	public:
		ray() {}
		ray(const glm::point3& origin, const glm::dvec3& direction) : orig{ origin }, dir{ direction } {}

		glm::point3 origin() const { return orig; }
		glm::dvec3 direction() const { return dir; }

		glm::point3 at(double t) const {
			return orig + t * dir;
		}
	private:
		glm::point3 orig;
		glm::dvec3 dir;
	};

}