export module raytracerlib.camera;
import raytracerlib;

export class camera {
public:
	constexpr camera() noexcept {
		constexpr auto aspect_ratio{ 16. / 9. };
		constexpr auto viewport_height{ 2. };
		constexpr auto viewport_width{ aspect_ratio * viewport_height };
		constexpr auto focal_length{ 1. };

		origin = { 0,0,0 };
		horizontal = { viewport_width,0.,0. };
		vertical = { 0.,viewport_height,0. };
		lower_left_corner = { origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length) };
	}

	constexpr const inline ray get_ray(double u, double v) const noexcept {
		return { origin,lower_left_corner + u * horizontal + v * vertical - origin };
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};