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

			constexpr T tan() const noexcept
				{return std::tan(m_value);}
          
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

			constexpr bool operator==(const Angle& b) const noexcept
				{return m_value==b.m_value;}
		
		private:
        	T m_value;
        };

	constexpr Angle<float> operator""_radf(long double val) noexcept
		{return Angle<float>(val);}

	constexpr Angle<float> operator""_degf(long double val) noexcept
		{return Angle<float>(pi<float>()*val/180.0f);}

	constexpr Angle<float> operator""_rf(long double val) noexcept
		{return Angle<float>(2.0f*pi<float>()*val);}

	constexpr Angle<double> operator""_rad(long double val) noexcept
		{return Angle<double>(val);}

	constexpr Angle<double> operator""_deg(long double val) noexcept
		{return Angle<double>(pi<double>()*val/180.0f);}

	constexpr Angle<double> operator""_r(long double val) noexcept
		{return Angle<double>(2.0f*pi<double>()*val);}

	template<class T>
	constexpr Angle<T> make_angle(Direction<T> a,Direction<T> b) noexcept
		{return Angle<T>(a,b);}


	template<class T>
	constexpr T operator/(Angle<T> u,Angle<T> v)
		{return static_cast<T>(u)/static_cast<T>(v);}

	template<class T>
	Angle<T> operator+(Angle<T> u,Angle<T> v)
		{return u+=v;}

	template<class T>
	T operator-(Angle<T> u,Angle<T> v)
		{return u-=v;}

	static_assert((30.0_degf).sin()==0.5f,"Sine is broken");
	static_assert(std::abs((60.0_degf).cos() - 0.5f)<1.0e-7f,"Cosine is broken");
	static_assert((45.0_degf).sin()==(45.0_degf).cos(),"hmm");
	static_assert((45.0_degf).tan()==1.0f,"Tangent is broken");
	static_assert(make_angle(x<float>(),y<float>())==90.0_degf,"Angle between directions is broken");
	}

#endif