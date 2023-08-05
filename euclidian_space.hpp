#ifndef GEOSIMD_EUCLIDIAN_SPACE_HPP
#define GEOSIMD_EUCLIDIAN_SPACE_HPP

#include "./vec_t.hpp"
#include "./metric_normed_space.hpp"
#include "./hilbert_space.hpp"
#include "./basic_point.hpp"
#include "./basic_vector.hpp"
#include "./unit_vector.hpp"

namespace geosimd
{
	namespace euclidian_space_impl
	{
		template<size_t N>
		requires(N != 0)
		struct dimension_tag_enabler;

		template<>
		struct dimension_tag_enabler<1>
		{
			using x = dimension_tag<0>;
		};

		template<>
		struct dimension_tag_enabler<2>:public dimension_tag_enabler<1>
		{
			using y = dimension_tag<1>;
		};

		template<size_t N>
		requires(N != 0)
		struct dimension_tag_enabler:public dimension_tag_enabler<2>
		{
			using z = dimension_tag<2>;
		};
	}

	template<class T, size_t N>
	struct euclidian_space :
		metric_normed_space_mixin<vec_t<T, N + 1>, hilbert_space_mixin<vec_t<T, N + 1>>>,
		euclidian_space_impl::dimension_tag_enabler<N>
	{
		using enable_homogenous_coordinates_t = void;
		using enable_rotations_t = void;

		using location = basic_point<euclidian_space<T, N>>;
		using displacement = basic_vector<euclidian_space<T, N>>;
		using direction = unit_vector<euclidian_space<T, N>>;
	};

	// Apparently, before euclidian_space can work, it must be checked with some independent concept
	static_assert(hilbert_space<euclidian_space<float, 3>>);
}

#endif