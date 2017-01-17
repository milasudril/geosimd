//@	{"targets":[{"name":"linesegment.hpp","type":"include"}]}

#ifndef GEOSIMD_LINESEGMENT_HPP
#define GEOSIMD_LINESEGMENT_HPP

#include "point.hpp"

namespace GeoSIMD
	{
	template<class T>
	struct LineSegment
		{
		explicit constexpr LineSegment(Point<T> from,Point<T> to):
			m_from(from),m_to(to)
			{}

		Point<T> m_from;
		Point<T> m_to;
		};

	template<class T>
	inline constexpr T length_squared(const LineSegment<T>& segment) noexcept
		{return distance_squared(segment.m_to,segment.m_from);}

	static_assert(
		length_squared(LineSegment<float>(origin<float>(),Point<float>{1.0f,1.0f,1.0f}))==3.0f
			,"length_squared broken");
	}

#endif
