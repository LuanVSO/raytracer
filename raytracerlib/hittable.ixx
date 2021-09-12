export module raytracerlib.hittable;
import raytracerlib.ray;
import glm.vec3;

export namespace rtl {
	struct hit_record {
		glm::point3 p;
		glm::dvec3 normal;
		double t;
		bool front_face;
		inline void set_face_normal(const ray& r, const glm::dvec3& outward_normal) noexcept {
			front_face = glm::dot(r.direction(),  outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	};

	class hittable {
	public:
		const virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const noexcept = 0;
		hittable() = default;
		hittable(const hittable & other) = default;
		hittable(hittable && other) = default;
		virtual ~hittable() noexcept = default;
	};
} // namespace rtl