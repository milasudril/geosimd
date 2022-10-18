#ifndef GEOSIMD_LINE_HPP
#define GEOSIMD_LINE_HPP

#include "./metric_normed_space.hpp"
#include "./unit_vector.hpp"
#include "./basic_point.hpp"

namespace geosimd
{
	template<metric_normed_space V>
	struct line
	{
		basic_point<V> origin;
		unit_vector<V> direction;
	};
}

#endif
