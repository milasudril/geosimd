//@	{"targets":[{"name":"angle.hpp","type":"include"}]}

#ifndef GEOSIMD_ANGLE_HPP
#define GEOSIMD_ANGLE_HPP

#include "constants.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Angle
		{
		public:
			explicit constexpr Angle(T value) noexcept:m_value(value)
				{}
          
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

			constexpr bool operator==(const Angle& b) const noexcept
				{return m_value==b.m_value;}

			constexpr Angle<T> operator-() const noexcept
				{return Angle<T>(-m_value);}

			explicit constexpr operator double() const noexcept
				{return static_cast<double>(m_value);}

			explicit constexpr operator float() const noexcept
				{return static_cast<float>(m_value);}
				
		
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
	constexpr T operator/(Angle<T> u,Angle<T> v) noexcept
		{return static_cast<T>(u)/static_cast<T>(v);}

	template<class T>
	constexpr Angle<T> operator+(Angle<T> u,Angle<T> v) noexcept
		{return u+=v;}

	template<class T>
	constexpr Angle<T> operator-(Angle<T> u,Angle<T> v) noexcept
		{return u-=v;}

	template<class T>
	constexpr Angle<T> operator/(Angle<T> u,T c) noexcept
		{return u/=c;}

	template<class T>
	constexpr Angle<T> operator*(Angle<T> u,T c) noexcept
		{return u*=c;}

	template<class U,class T>
	constexpr U sin(Angle<T> x)
		{return std::sin(static_cast<U>(x));}

	template<class U,class T>
	constexpr U cos(Angle<T> x)
		{return std::cos(static_cast<U>(x));}

	template<class U,class T>
	constexpr U tan(Angle<T> x)
		{return std::tan(static_cast<U>(x));}

	static_assert(sin<float>(30.0_degf)==0.5f,"Sine is broken");
	static_assert(std::abs(cos<float>(60.0_degf) - 0.5f)<1.0e-7f,"Cosine is broken");
	static_assert(sin<float>(45.0_degf)==cos<float>(45.0_degf),"hmm");
	static_assert(tan<float>(45.0_degf)==1.0f,"Tangent is broken");
	}

#endif