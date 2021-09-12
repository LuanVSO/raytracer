module;
#include <cmath>
export module raytracerlib.sphere;
import raytracerlib.hittable;
import glm.vec3;


export namespace rtl {
	class sphere : public hittable {
	public:
		sphere() noexcept {}
		sphere(glm::point3 cen, double rad) noexcept :center{ cen }, radius{ rad } {}

		const bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const noexcept override final {
			const auto oc{ r.origin() - center };
			const auto a{ glm::legth_squared(r.direction()) };
			const auto half_b{ glm::dot(oc,r.direction()) };
			const auto c{ glm::legth_squared(oc) - radius * radius };
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
			const auto outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);

			return true;
		}

		glm::point3 center;
		double radius;
	};
}