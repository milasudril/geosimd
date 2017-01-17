//@	{"targets":[{"name":"sphere.hpp","type":"include"}]}

#ifndef GEOSIMD_SPHERE_HPP
#define GEOSIMD_SPHERE_HPP

#include "point.hpp"

namespace GeoSIMD
	{
	template<class T>
	struct Sphere
		{
		explicit constexpr Sphere(Point<T> origin,T radius) noexcept:
			m_origin(origin),m_radius(radius)
			{}

			constexpr T radius() const noexcept
				{return m_radius;}

			constexpr T& radius() noexcept
				{return m_radius;}
			
			Point<T> origin() const noexcept
				{return m_origin;}

			constexpr void move(const Point<T> origin) noexcept
				{m_origin=origin;}

		private:
//TODO: This sphere is twice as large as needed, but it is SIMD aligned.
//	What is best?
			Point<T> m_origin;
			T m_radius;
		};

	template<class T>
	inline constexpr T volume(const Sphere<T>& obj) noexcept
		{
		auto r=obj.radius();
		return static_cast<T>(4)*pi<T>()*r*r*r/static_cast<T>(3);
		}

	template<class T>
	inline constexpr T area(const Sphere<T>& obj) noexcept
		{
		auto r=obj.radius();
		return static_cast<T>(4)*pi<T>()*r*r;
		}

	template<class T>
	inline constexpr T centroid(const Sphere<T>& obj) noexcept
		{return obj.origin();}

	template<class T>
	inline constexpr T distance(const Sphere<T>& a,const Sphere<T>& b)
		{
		return std::sqrt(distance_squared(a.origin(),b.origin())) - (a.radius() + b.radius());
		}
	}

#endif
