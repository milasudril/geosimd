#ifndef GEOSIMD_DIRECTION_HPP
#define GEOSIMD_DIRECTION_HPP

#include "vector.hpp"
#include "rotation.hpp"
#include <cmath>

namespace GeoSIMD
	{
	template<class T>
	class Direction
		{
		public:
			constexpr explicit Direction(Vector<T> v)
				:m_data( (v/std::sqrt(GeoSIMD::dot(v,v))).data() )
				{}

			constexpr T x() const noexcept
				{return m_data[0];}

			constexpr T y() const noexcept
				{return m_data[1];}

			constexpr T z() const noexcept
				{return m_data[2];}

			constexpr bool operator==(Direction v) const noexcept
				{
                return m_data[0]==v.m_data[0]
                  	&& m_data[1]==v.m_data[1]
					&& m_data[2]==v.m_data[2];
                }

			constexpr T dot(Direction v) const noexcept
				{
				auto temp=m_data*v.m_data;
				return temp[0] + temp[1] + temp[2];
				}

			constexpr vec4_t<T> data() const noexcept
				{return m_data;}

			explicit constexpr operator Vector<T>() const noexcept
				{return Vector<T>(x(),y(),z());}

			Direction& transform(const Rotation<T>& R) noexcept
				{
				const auto& R_data=R.data();
				vec4_t<T> temp;
				for(int k=0;k<4;++k)
					{
					auto row=vec4_t<T>
						{R_data(k,0),R_data(k,1),R_data(k,2),R_data(k,3)};
					temp[k]=GeoSIMD::dot<T>(m_data,row);
					}
				m_data=temp;
				return *this;
				}

		private:
			vec4_t<T> m_data;
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

	template<class U,class T>
	constexpr Angle<U> angle(Direction<T> a,Direction<T> b) noexcept
		{return Angle<U>(std::acos(dot(a,b)));}

	
	}

#endif