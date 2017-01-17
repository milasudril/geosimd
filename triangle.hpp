//@	{"targets":[{"name":"triangle.hpp","type":"include"}]}

#ifndef GEOSIMD_TRIANGLE_HPP
#define GEOSIMD_TRIANGLE_HPP

#include "point.hpp"

namespace GeoSIMD
	{
	template<class T>
	struct Triangle
		{
		Point<T> A;
		Point<T> B;
		Point<T> C;
		};

	template<class T>
	inline constexpr Vector<T> normal(const Triangle<T>& obj) noexcept
		{
		auto AB=obj.B - obj.A;
		auto AC=obj.C - obj.A;
		return cross(AB,AC);
		}
		
	template<class T>
	inline constexpr T area(const Triangle<T>& obj) noexcept
		{
		std::sqrt( length_squared(normal(obj)) )/static_cast<T>(2);
		}

	template<class T>
	inline constexpr T centroid(const Triangle<T>& obj) noexcept
		{return centroid({obj.A,obj.B,obj.C});}
	}

#endif
