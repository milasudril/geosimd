//@	{"targets":[{"name":"line.hpp","type":"include"}]}

#ifndef GEOSIMD_LINE_HPP
#define GEOSIMD_LINE_HPP

#include "point.hpp"
#include "direction.hpp"

namespace GeoSIMD
	{
	template<class T>
	struct Line
		{
		explicit constexpr Line(Point<T> origin,Direction<T> direction):
			m_origin(origin),m_direction(direction)
			{}

		Point<T> m_origin;
		Direction<T> m_direction;
		};
	}

#endif
