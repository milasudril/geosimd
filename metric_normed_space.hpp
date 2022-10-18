#ifndef GEOSIMD_METRIC_NORMED_SPACE_HPP
#define GEOSIMD_METRIC_NORMED_SPACE_HPP

#include "./abstract_spaces.hpp"

namespace geosimd
{
	template<class PointType, normed_space V>
	struct metric_normed_space_mixin: public V
	{
		using point_type = PointType;
		using vector_space = V;
		using vector_type = vector_space::vector_type;
		using scalar_type = vector_space::scalar_type;

		static constexpr auto distance(point_type a, point_type b)
		{ return vector_space::norm(a - b); }

		static constexpr auto distance_squared(point_type a, point_type b)
		{ return vector_space::norm_squared(a - b); }
	};

	template<class V>
	concept metric_normed_space
		=  metric_space<V>
		&& normed_space<V>
		&& std::is_base_of_v<
			metric_normed_space_mixin<typename V::point_type, typename V::normed_space>, V>;
}

#endif