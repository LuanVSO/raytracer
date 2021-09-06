module;
#include <cmath>
export module raytracerlib.sphere;
import raytracerlib.hittable;
import raytracerlib.vec3;


export {
	class sphere : public hittable {
	public:
		constexpr sphere() noexcept {}
		constexpr sphere(point3 cen, double rad) noexcept :center{ cen }, radius{ rad } {}
		constexpr virtual ~sphere() noexcept override = default;

		const virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const noexcept override;

		point3 center;
		double radius;
	};

	const bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const noexcept
	{
		const vec3 oc{ r.origin() - center };
		const auto a{ r.direction().lenght_squared() };
		const auto half_b{ dot(oc,r.direction()) };
		const auto c{ oc.lenght_squared() - radius * radius };
		const auto discriminant{ half_b * half_b - a * c };
		if (discriminant < 0)
			return false;
		const auto sqrtd{ std::sqrt(discriminant) };
		auto root{ (-half_b - sqrtd) / a };
		if (root < t_min || t_max < root) {
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}
		rec.t = root;
		rec.p = r.at(rec.t);
		const vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}
}