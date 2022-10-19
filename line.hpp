#ifndef GEOSIMD_LINE_HPP
#define GEOSIMD_LINE_HPP

#include "./abstract_spaces.hpp"
#include "./basic_point.hpp"

namespace geosimd
{
	template<affine_space V>
	struct line
	{
		basic_point<V> p1;
		basic_point<V> p2;
	};
}

#endif
