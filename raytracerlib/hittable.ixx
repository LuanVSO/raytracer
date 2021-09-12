module;
#include <memory>
export module raytracerlib.hittable;
import raytracerlib.ray;
import glm.vec3;
export import raytracerlib.material;

export namespace rtl {

	class hittable {
	public:
		const virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const noexcept = 0;
		hittable() = default;
		hittable(const hittable & other) = default;
		hittable(hittable && other) = default;
		virtual ~hittable() noexcept = default;
	};
} // namespace rtl