#ifndef GEOSIMD_LINE_HPP
#define GEOSIMD_LINE_HPP

#include "./abstract_spaces.hpp"
#include "./basic_point.hpp"
#include "./hilbert_space.hpp"

#include <array>
#include <algorithm>

namespace geosimd
{
	template<class T>
	requires(std::is_floating_point_v<T>)
	class line_parameter
	{
	public:
		GEOSIMD_INLINE_OPT constexpr explicit line_parameter(T val):m_value{val}{}
		GEOSIMD_INLINE_OPT constexpr auto get() const { return m_value; }

	private:
		T m_value;
	};

	template<affine_space V>
	struct line
	{
		basic_point<V> p1;
		basic_point<V> p2;

		GEOSIMD_INLINE_OPT static constexpr auto valid(line_parameter<typename V::scalar_type>)
		{ return true; }

		GEOSIMD_INLINE_OPT static constexpr auto clamp(line_parameter<typename V::scalar_type> val)
		{ return val; }
	};

	template<class T>
	requires(std::is_floating_point_v<T>)
	line_parameter<T> max(line_parameter<T> a, T b)
	{
		return line_parameter{std::max(a.get(), b)};
	}

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto point_at(line<V> const& line,
		line_parameter<typename V::scalar_type> param)
	{
		return lerp(line.p1, line.p2, param.get());
	}

	template<inner_product_space V>
	constexpr auto project(line<V> const& line, basic_point<V> loc)
	{
		auto const d = line.p2 - line.p1;
		auto const r = loc - line.p1;
		return line_parameter{inner_product(r, d)/inner_product(d)};
	}

	template<hilbert_space V>
	constexpr auto get_closest_points(line<V> const& line, basic_point<V> loc)
	{
		auto const proj = project(line, loc);
		return point_pair{point_at(line, proj), loc};
	}


	template<class T>
	struct line_intersection
	{
		line_parameter<T> a;
		line_parameter<T> b;
	};

	template<hilbert_space V>
	requires(std::is_floating_point_v<typename V::scalar_type>)
	constexpr auto intersection(line<V> const& a, line<V> const& b)
	{
		auto const d_a = a.p2 - a.p1;
		auto const d_b = b.p2 - b.p1;
		auto const d_o = a.p1 - b.p1;

		auto const a11 =  inner_product(d_a);
		auto const a12 = -inner_product(d_a, d_b);
		auto const a21 = -a12;
		auto const a22 = -inner_product(d_b);

		auto const rhs_a = -inner_product(d_a, d_o);
		auto const rhs_b = -inner_product(d_b, d_o);

		auto const denom = a11*a22 - a12*a21;
		auto const s = line_parameter{ (a22*rhs_a - a12*rhs_b)/denom};
		auto const t = line_parameter{-(a21*rhs_a - a11*rhs_b)/denom};
		return line_intersection{s, t};

	}

	template<hilbert_space V>
	constexpr auto get_closest_points(line<V> const& a, line<V> const& b)
	{
		auto const intersect = intersection(a, b);
		auto const loc_a = point_at(a, intersect.a);
		auto const loc_b = point_at(b, intersect.b);
		return point_pair{loc_a, loc_b};
	}


	template<affine_space V>
	struct ray
	{
		basic_point<V> origin;
		basic_point<V> target;

		GEOSIMD_INLINE_OPT static constexpr auto valid(line_parameter<typename V::scalar_type> val)
		{ return val.get() >= zero(empty<typename V::scalar_type>{}); }

		GEOSIMD_INLINE_OPT static constexpr auto clamp(line_parameter<typename V::scalar_type> val)
		{ return line_parameter{std::max(val.get(), zero(empty<typename V::scalar_type>{}))}; }
	};

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto extension(ray<V> const& v)
	{ return line{v.origin, v.target}; }

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto point_at(ray<V> const& ray,
		line_parameter<typename V::scalar_type> param)
	{
		return lerp(ray.origin, ray.target, param.get());
	}

	template<hilbert_space V>
	constexpr auto get_closest_points(line<V> const& a, ray<V> const b)
	{
		auto const intersect = intersection(a, extension(b));
		auto const loc_b = point_at(b, ray<V>::clamp(intersect.b));
		auto const loc_a = point_at(a, project(a, loc_b));
		return point_pair{loc_a, loc_b};
	}

	template<hilbert_space V>
	constexpr auto get_closest_points(ray<V> const& a, ray<V> const& b)
	{
		auto const intersect = intersection(extension(a), extension(b));
		if(ray<V>::valid(intersect.a))
		{
			if(ray<V>::valid(intersect.b))
			{
				auto const loc_a = point_at(a, intersect.a);
				auto const loc_b = point_at(b, intersect.b);
				return point_pair{loc_a, loc_b};
			}
			else
			{
				auto const proj = project(extension(a), b.origin);
				auto const loc_a = point_at(extension(a), proj);
				return point_pair{loc_a, b.origin};
			}
		}
		else
		{
			if(ray<V>::valid(intersect.b))
			{
				auto const proj = project(extension(b), a.origin);
				auto const loc_b = point_at(extension(b), proj);
				return point_pair{a.origin, loc_b};
			}
			else
			{
				auto const proj_a_on_b = project(extension(b), a.origin);
				if(ray<V>::valid(proj_a_on_b))
				{
					return point_pair{a.origin, point_at(extension(b), proj_a_on_b)};
				}
				else
				{
					auto const proj_b_on_a = project(extension(a), b.origin);
					if(ray<V>::valid(proj_b_on_a))
					{
						return point_pair{point_at(extension(a), proj_b_on_a), b.origin};
					}
					else
					{
						return point_pair{a.origin, b.origin};
					}
				}
			}
		}
	}

	template<affine_space V>
	struct line_segment
	{
		basic_point<V> p1;
		basic_point<V> p2;

		GEOSIMD_INLINE_OPT static constexpr auto valid(line_parameter<typename V::scalar_type> val)
		{
			return val.get() >= zero(empty<typename V::scalar_type>{})
				&& val.get() <= one(empty<typename V::scalar_type>{});
		}

		GEOSIMD_INLINE_OPT static constexpr auto clamp(line_parameter<typename V::scalar_type> val)
		{
			return line_parameter{std::clamp(val.get(),
				zero(empty<typename V::scalar_type>{}),
				one(empty<typename V::scalar_type>{})
			)};
		}
	};

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto flip(line_segment<V> const& a)
	{
		return line_segment{a.p2, a.p1};
	}

	template<metric_space V>
	GEOSIMD_INLINE_OPT constexpr auto length(line_segment<V> const& val)
	{
		return distance(val.p1, val.p2);
	}

	template<hilbert_space V>
	GEOSIMD_INLINE_OPT constexpr auto length_squared(line_segment<V> const& val)
	{
		return distance_squared(val.p1, val.p2);
	}

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto extension(line_segment<V> const& v)
	{ return line{v.p1, v.p2}; }

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto point_at(line_segment<V> const& l,
		line_parameter<typename V::scalar_type> param)
	{
		return lerp(l.p1, l.p2, param.get());
	}

	template<hilbert_space V>
	constexpr auto get_closest_points(line_segment<V> const& a, line_segment<V> const& b)
	{
		auto const intersect = intersection(extension(a), extension(b));
		if(line_segment<V>::valid(intersect.a)) [[unlikely]]
		{
			if(line_segment<V>::valid(intersect.b)) [[unlikely]]
			{
				auto const loc_a = point_at(a, intersect.a);
				auto const loc_b = point_at(b, intersect.b);
				return point_pair{loc_a, loc_b};
			}
			else
			{
				auto const loc_b = point_at(extension(b), line_segment<V>::clamp(intersect.b));
				auto const proj = line_segment<V>::clamp(project(extension(a), loc_b));
				auto const loc_a = point_at(extension(a), proj);
				return point_pair{loc_a, loc_b};
			}
		}
		else
		{
			if(line_segment<V>::valid(intersect.b)) [[unlikely]]
			{
				auto const loc_a = point_at(extension(a), line_segment<V>::clamp(intersect.a));
				auto const proj = line_segment<V>::clamp(project(extension(b), loc_a));
				auto const loc_b = point_at(extension(b), proj);
				return point_pair{loc_a, loc_b};
			}
			else
			{
				auto const param_a = line_segment<V>::clamp(intersect.a);
				auto const loc_a = point_at(extension(a), param_a);
				auto const proj_a_on_b = project(extension(b), loc_a);
				if(line_segment<V>::valid(proj_a_on_b))
				{
					return point_pair{loc_a, point_at(extension(b), proj_a_on_b)};
				}
				else
				{
					auto const param_b = line_segment<V>::clamp(intersect.b);
					auto const loc_b = point_at(extension(b), param_b);
					auto const proj_b_on_a = project(extension(a), loc_b);
					if(line_segment<V>::valid(proj_b_on_a))
					{
						return point_pair{point_at(extension(a), proj_b_on_a), loc_b};
					}
					else
					{
						auto const a_start = a.p1;
						auto const a_end = a.p2;
						auto const b_start = b.p1;
						auto const b_end = b.p2;

						std::array<point_pair<V>, 4> pairs{
							point_pair{a_start, b_start},
							point_pair{a_start, b_end},
							point_pair{a_end, b_start},
							point_pair{a_end, b_end}
						};

						return *std::ranges::min_element(pairs, [](auto p1, auto p2){
							return p1.get_distance_squared() < p2.get_distance_squared();
						});
					}
				}
			}
		}
	}
}

#endif
