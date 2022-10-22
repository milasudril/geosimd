#ifndef GEOSIMD_LINE_HPP
#define GEOSIMD_LINE_HPP

#include "./abstract_spaces.hpp"
#include "./basic_point.hpp"
#include "./hilbert_space.hpp"

namespace geosimd
{
	template<affine_space V>
	struct line
	{
		basic_point<V> p1;
		basic_point<V> p2;
	};

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
	struct closest_points
	{
		basic_point<V> a;
		basic_point<V> b;
	};


	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto point_at(line<V> const& line,
		line_parameter<typename V::scalar_type> param)
	{
		return lerp(line.p1, line.p2, param.get());
	}

	template<hilbert_space V>
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
		return closest_points{point_at(line, proj), loc};
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

		auto const a11 = inner_product(d_a);
		auto const a12 = -inner_product(d_a, d_b);
		auto const a21 = -a12;
		auto const a22 = -inner_product(d_b);

		auto const rhs_a = -inner_product(d_a, d_o);
		auto const rhs_b = -inner_product(d_b, d_o);

		auto const denom = a11*a22 - a12*a21;
		auto const s =  line_parameter{(a22*rhs_a - a12*rhs_b)/denom};
		auto const t = line_parameter{-(a21*rhs_a - a11*rhs_b)/denom};
		return line_intersection{s, t};

	}

	template<hilbert_space V>
	constexpr auto get_closest_points(line<V> const& a, line<V> const& b)
	{
		auto const intersect = intersection(a, b);
		auto const loc_a = point_at(a, intersect.a);
		auto const loc_b = point_at(b, intersect.b);
		return closest_points{loc_a, loc_b};
	}

	template<hilbert_space V>
	constexpr auto min_distance_squared(line<V> const& a, line<V> const& b)
	{
		auto const points = get_closest_points(a, b);
		return distance_squared(points.a, points.b);
	}

	template<hilbert_space V>
	constexpr auto min_distance(line<V> const& a, line<V> const& b)
	{
		return std::sqrt(min_distance_squared(a, b));
	}

	template<affine_space V>
	struct ray
	{
		basic_point<V> origin;
		basic_point<V> target;
	};

	template<affine_space V>
	auto extension(ray<V> const& v)
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
		if(intersect.b >= zero(empty<typename V::scalar_type>{}))
		{
			auto const loc_a = point_at(a, intersect.a);
			auto const loc_b = point_at(b, intersect.b);
			return closest_points{loc_a, loc_b};
		}

		return get_closest_points(a, b.origin);
	}

}

#endif
