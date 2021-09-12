module;
#include <memory>
#include <vector>

export module raytracerlib.hittable_list;
import raytracerlib.hittable;
import raytracerlib.ray;

using std::unique_ptr, std::make_shared;

export namespace rtl {
	class hittable_list : public hittable
	{
	public:
		hittable_list() {}
		hittable_list(unique_ptr<hittable>&& object) { add(std::move(object)); }

		void clear() { objects.clear(); }
		void add(unique_ptr<hittable> object) { objects.emplace_back(std::move(object)); }

		const bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const noexcept override final {
			hit_record temp_rec;
			bool hit_any{ false };
			auto closest_so_far{ t_max };
			for (auto&& object : objects) {
				if (object->hit(r, t_min, closest_so_far, temp_rec)) {
					hit_any = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}
			return hit_any;
		}

	private:
		std::vector<unique_ptr<hittable>> objects;
	};
}