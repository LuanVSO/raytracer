export module raytracerlib.camera;
import raytracerlib.helpers;
import glm.vec3;
import raytracerlib.ray;

constexpr auto aspect_ratio{ 16. / 9. };
constexpr auto viewport_height{ 2. };
constexpr auto viewport_width{ aspect_ratio * viewport_height };
constexpr auto focal_length{ 1. };
constexpr glm::dvec3 fl_vec{ 0, 0, focal_length };
export namespace rtl {
	class camera {
	public:
		camera() noexcept : origin{ 0,0,0 }, horizontal{ viewport_width,0.,0. },
			vertical{ 0.,viewport_height,0.} {
			lower_left_corner = { origin - horizontal / 2. - vertical / 2. - fl_vec};
		}

		const inline ray get_ray(double u, double v) const noexcept {
			return { origin,lower_left_corner + u * horizontal + v * vertical - origin };
		}

	private:
		glm::point3 origin;
		glm::point3 lower_left_corner;
		glm::dvec3 horizontal;
		glm::dvec3 vertical;
	};
}