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

	template<affine_space V>
	constexpr auto point_at(line<V> const& line, typename V::scalar_type param)
	{
		return lerp(line.p1, line.p2, param);
	}

	template<class T>
	struct line_intersection
	{
		T a;
		T b;
	};

	template<hilbert_space V>
	requires(std::is_floating_point_v<typename V::scalar_type>)
	constexpr auto intersection(line<V> const& a, line<V> const& b)
	{
		auto const d_a = a.p2 - a.p1;
		auto const d_b = b.p2 - b.p1;
		auto const d_o = a.p1 - b.p1;

		auto const a11 = inner_product(d_a, d_a);
		auto const a12 = -inner_product(d_a, d_b);
		auto const a21 = -a12;
		auto const a22 = -inner_product(d_b, d_b);

		auto const rhs_a = -inner_product(d_a, d_o);
		auto const rhs_b = -inner_product(d_b, d_o);

		auto const denom = a11*a22 - a12*a21;
		auto const s =  (a22*rhs_a - a12*rhs_b)/denom;
		auto const t = -(a21*rhs_a - a11*rhs_b)/denom;
		return line_intersection{s, t};

	}
}

#endif
