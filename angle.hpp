#ifndef GEOSIMD_ANGLE_HPP
#define GEOSIMD_ANGLE_HPP

#include "direction.hpp"
#include <cmath>

namespace GeoSIMD
	{
	template<class T>
	class Angle
		{
		public:
        	explicit constexpr Angle(T value) noexcept:m_value(value)
				{}
			
			explicit constexpr Angle(Direction<T> a,Direction<T> b) noexcept:
          		m_value(std::acos(dot(a,b)))
				{}
          
       		constexpr T cos() const noexcept
				{return std::cos(m_value);}
          
			constexpr T sin() const noexcept
				{return std::sin(m_value);}
          
			constexpr Angle& operator+=(Angle a) noexcept
				{
				m_value+=a.m_value;
				return *this;
				}

			constexpr Angle& operator-=(Angle a) noexcept
				{
				m_value-=a.m_value;
				return *this;
				}

			constexpr Angle& operator*=(T c) noexcept
				{
				m_value*=c;
				return *this;
				}

			constexpr Angle& operator/=(T c) noexcept
				{
				m_value/=c;
				return *this;
				}

			constexpr explicit operator T() const noexcept
				{return m_value;}
		
		private:
        	T m_value;
        };

	template<class T>
	constexpr T operator/(Angle<T> u,Angle<T> v)
		{return static_cast<T>(u)/static_cast<T>(v);}

	template<class T>
	Angle<T> operator+(Angle<T> u,Angle<T> v)
		{return u+=v;}

	template<class T>
	T operator-(Angle<T> u,Angle<T> v)
		{return u-=v;}
	}

#endif