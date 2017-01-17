//@	{"targets":[{"name":"cuboidaligned.hpp","type":"include"}]}

#ifndef GEOSIMD_CUBOIDALIGNED_HPP
#define GEOSIMD_CUBOIDALIGNED_HPP

#include "point.hpp"
#include "vector.hpp"

namespace GeoSIMD
	{
	template<class T>
	struct CuboidAligned
		{
		explicit constexpr CuboidAligned(Point<T> origin,Vector<T> extents) noexcept:
			m_origin(origin),m_extents(extents)
			{}

		explicit constexpr CuboidAligned(Point<T> min,Point<T> max) noexcept:
			m_origin(centroid({min,max})),m_extents((max - min)/static_cast<T>(2))
			{}

		constexpr Point<T> min() noexcept
			{return m_origin - m_extents;}

		constexpr Point<T> max() noexcept
			{return m_origin + m_extents;}

		Point<T> m_origin;
		Vector<T> m_extents;
		};

	template<class T>
	constexpr T volume(const CuboidAligned<T>& obj) noexcept
		{
		auto size=static_cast<T>(2)*obj.m_extents;
		return size.x()*size.y()*size.z();
		}

	template<class T>
	constexpr T area(const CuboidAligned<T>& obj) noexcept
		{
		auto size=static_cast<T>(4)*obj.m_extents;
		return size.x()*size.y() + size.x()*size.z() + size.y()*size.z();
		}

	template<class T>
	constexpr T centroid(const CuboidAligned<T>& obj) noexcept
		{return obj.m_origin;}
	}

#endif
