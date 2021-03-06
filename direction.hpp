//@	{"targets":[{"name":"direction.hpp","type":"include"}]}

#ifndef GEOSIMD_DIRECTION_HPP
#define GEOSIMD_DIRECTION_HPP

#include "vector.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Direction;

	template<class T>
	Direction<T> transform(Direction<T> dir,const Rotation<T>& R) noexcept;

	template<class T>
	class Direction:private Vector<T>
		{
		public:
			using Vector<T>::data;
			using typename Vector<T>::Representation;

			constexpr explicit Direction(Vector<T> v)
				:Vector<T>( v/std::sqrt(GeoSIMD::dot(v,v)) )
				{}

			constexpr T x() const noexcept
				{return Vector<T>::x();}

			constexpr T y() const noexcept
				{return Vector<T>::y();}

			constexpr T z() const noexcept
				{return Vector<T>::z();}

			constexpr bool operator==(Direction v) const noexcept
				{return Vector<T>::operator==(v);}

			constexpr T dot(Direction v) const noexcept
				{return Vector<T>::dot(v);}

			template<class U>
			constexpr Vector<U> operator*(U c) const noexcept
				{return c*(*this);}


		private:
			Direction(){}
			friend Direction<T> transform<>(Direction<T> dir,const Rotation<T>& R) noexcept;
		};

	template<class T>
	constexpr Direction<T> x() noexcept;

	template<class T>
	constexpr Direction<T> y() noexcept;

	template<class T>
	constexpr Direction<T> z() noexcept;

#ifdef __SSE__
	template<>
	constexpr Direction<float> x<float>() noexcept
		{return Direction<float>(1.0_xf);}

	template<>
	constexpr Direction<float> y<float>() noexcept
		{return Direction<float>(1.0_yf);}

	template<>
	constexpr Direction<float> z<float>() noexcept
		{return Direction<float>(1.0_zf);}
#endif

#ifdef __AVX__
	template<>
	constexpr Direction<double> x<double>() noexcept
		{return Direction<double>(1.0_x);}

	template<>
	constexpr Direction<double> y<double>() noexcept
		{return Direction<double>(1.0_y);}

	template<>
	constexpr Direction<double> z<double>() noexcept
		{return Direction<double>(1.0_z);}
#endif

	template<class T>
	constexpr T dot(Direction<T> a,Direction<T> b) noexcept
		{return a.dot(b);}

	static_assert(dot(x<float>(),y<float>())==0.0f,"Dot product broken");
	static_assert(dot(x<float>(),x<float>())==1.0f,"Dot product broken");

	template<class T,class U=T>
	constexpr Angle<U> angle(Direction<T> a,Direction<T> b) noexcept
		{return Angle<U>(std::acos(dot(a,b)));}
	static_assert(angle(x<float>(),y<float>())==90.0_degf,"Bad angle between vectors");

	template<class T>
	inline Direction<T> transform(Direction<T> dir,const Rotation<T>& R) noexcept
		{
		Direction<T> ret;
		ret.m_data=R.matrix()*dir.data();
		return ret;
		}
	}

#endif