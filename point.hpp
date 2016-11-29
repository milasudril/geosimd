#ifndef GEOSIMD_POINT_HPP
#define GEOSIMD_POINT_HPP

#include "vector.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Point
		{
		public:
			constexpr explicit Point(T x,T y,T z):m_data{x,y,z,one<T>()}
				{}

			constexpr T x() const noexcept
				{return m_data[0];}

			constexpr T& x() noexcept
				{return m_data[0];}

			constexpr T y() const noexcept
				{return m_data[1];}

			constexpr T& y() noexcept
				{return m_data[1];}

			constexpr T z() const noexcept
				{return m_data[2];}

			constexpr T& z() noexcept
				{return m_data[2];}

			constexpr Point& operator+=(Vector<T> v) noexcept
				{
				m_data+=v.data();
				return *this;
				}

			constexpr Point& operator-=(Vector<T> v) noexcept
				{
				m_data-=v.data();
				return *this;
				}

			constexpr bool operator==(Point v) const noexcept
				{
                return m_data[0]==v.m_data[0]
                  	&& m_data[1]==v.m_data[1]
					&& m_data[2]==v.m_data[2];
                }

			constexpr vec4_t<T> data() const noexcept
				{return m_data;}

		private:
			vec4_t<T> m_data;
		};

	template<class T>
	constexpr Point<T> origin() noexcept
		{return Point<T>(zero<T>(),zero<T>(),zero<T>());}

	template<class T>
	constexpr Point<T> operator+(Point<T> a,Vector<T> b) noexcept
		{return a+=b;}

	template<class T>
	constexpr Point<T> operator-(Point<T> a,Vector<T> b) noexcept
		{return a-=b;}

	template<class T>
	constexpr Vector<T> operator-(Point<T> a,Point<T> b) noexcept
		{return a.data() - b.data();}

	template<class T>
	constexpr T dist_2(Point<T> a,Point<T> b) noexcept
		{
		auto diff=a-b;
		return dot(diff,diff);
		}
	}

#endif
