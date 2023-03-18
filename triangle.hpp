#ifndef GEOSIMD_TRIANGLE_HPP
#define GEOSIMD_TRIANGLE_HPP

#include "./basic_point.hpp"
#include "./hilbert_space.hpp"

#include <algorithm>

namespace geosimd
{
	template<affine_space V>
	struct triangle
	{
		basic_point<V> p1;
		basic_point<V> p2;
		basic_point<V> p3;
	};

	template<class Func, class V, class ... Params>
	concept point_visitation_function =
	affine_space<V> && requires(Func f, basic_point<V> p, Params ... params)
	{
		{f(p, params...)} -> std::same_as<void>;
	};

	template<affine_space V, class Func, class ... FuncParams>
	requires point_visitation_function<Func, V, FuncParams...>
	void project_from_above(triangle<V> const& T, Func&& f, FuncParams&& ... params)
	{
		using scalar_type = V::scalar_type;

		auto by_y = [](basic_point<V> a, basic_point<V> b) {
			return a[1] < b[1];
		};

		std::array<basic_point<V>, 3> points{T.p1, T.p2, T.p3};
		std::ranges::sort(points, by_y);

		auto const bottom_corner = points[0];
		auto const mid_corner = points[1];
		auto const top_corner = points[2];

		auto const line_count = static_cast<size_t>(top_corner[1] - bottom_corner[1]);
		for(size_t k = 0; k != line_count; ++k)
		{
			auto const y = bottom_corner[1]
				+ (static_cast<scalar_type>(k) + static_cast<scalar_type>(0.5));

			auto const x2 = std::lerp(bottom_corner[0],
				top_corner[0],
				(y - bottom_corner[1])/(top_corner[1] - bottom_corner[1]));

			auto const x1 = (y < mid_corner[1]) ?
				  std::lerp(bottom_corner[0],
					mid_corner[0],
					(y - bottom_corner[1])/(mid_corner[1] - bottom_corner[1]))
				: std::lerp(mid_corner[0],
					top_corner[0],
					(y - mid_corner[1])/(top_corner[1] - mid_corner[1]));
			auto const col_count = static_cast<size_t>(std::abs(x1 - x2));
			auto const x0 = std::min(x1, x2);

			for(size_t l = 0; l != col_count; ++l)
			{
				auto const x = x0 + (static_cast<scalar_type>(l) + static_cast<scalar_type>(0.5));
				f(basic_point<V>{x, y, 1.0f}, params...);
			}
		}
	}
}

#endif
