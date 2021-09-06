export module raytracerlib.hittable;
import raytracerlib.ray;
import raytracerlib.vec3;

export struct hit_record {
	point3 p;
	vec3 normal;
	double t;
	bool front_face;
	constexpr inline void set_face_normal(const ray& r, const vec3& outward_normal) noexcept {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

export class hittable {
public:
	const virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const noexcept = 0;
	virtual ~hittable() noexcept = default;
};
