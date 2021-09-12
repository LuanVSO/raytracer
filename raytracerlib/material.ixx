module;
#include <memory>
export module raytracerlib.material;
import raytracerlib.ray;
import glm.vec3;


export namespace rtl {
	class material;
	struct hit_record {
		glm::point3 p;
		glm::dvec3 normal;
		std::shared_ptr<material> mat_ptr;
		double t;
		bool front_face;
		inline void set_face_normal(const ray& r, const glm::dvec3& outward_normal) noexcept {
			front_face = glm::dot(r.direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	};
	class material
	{
	public:
		virtual const bool scatter(
			const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered)const noexcept = 0;
	};

	class lambertian : public material {
	public:
		lambertian(const glm::color& a): albedo{a} {}
		const bool scatter(
			const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered
		) const noexcept override final {
			r_in;
			auto scatter_direction = rec.normal + glm::random_unit_vector();
			// catch degener9ate scatter direction
			if (near_zero(scatter_direction))
				scatter_direction = rec.normal;

			scattered = ray(rec.p, scatter_direction);
			attenuation = albedo;
			return true;
		}
	private:
		glm::color albedo;
	};
	class metal : public material {
	public:
		metal(const glm::color& a,double f): albedo{a}, fuzz(f<1?f:1){}
		const bool scatter(
			const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered
		) const noexcept override final {
			glm::dvec3 reflected = glm::reflect(glm::normalize(r_in.direction()), rec.normal);
			scattered = ray(rec.p, reflected+fuzz * glm::ballRand(1.));
			attenuation = albedo;
			return (glm::dot(scattered.direction(), rec.normal) > 0);
		}
	private:
		glm::color albedo;
		double fuzz;
	};
}