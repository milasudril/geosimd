#ifndef GEOSIMD_VECTOR_HPP
#define GEOSIMD_VECTOR_HPP

#include "storage.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Vector;

/*	template<class T>
	constexpr T dot(Vector<T> a,Vector<T> b);*/

	template<class T>
	class Vector
		{
		public:
			constexpr explicit Vector(T x,T y,T z):m_data{x,y,z,0}
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

			constexpr Vector& operator*=(T c) noexcept
				{
				m_data*=c;
				return *this;
				}

			constexpr Vector& operator/=(T c) noexcept
				{
				m_data/=c;
				return *this;
				}

			constexpr Vector& operator+=(Vector v) noexcept
				{
				m_data+=v;
				return *this;
				}

			constexpr Vector& operator-=(Vector v) noexcept
				{
				m_data-=v;
				return *this;
				}

			constexpr bool operator==(Vector v) const neoxcept
				{return m_data==v.m_data;}

		//	friend constexpr T dot<>(Vector a,Vector b);

			constexpr vec4_t<T> data() const noexcept
				{return m_data;}

		private:
			vec4_t<T> m_data;
		};

	template<class T>
	constexpr Vector<T> operator*(T c,Vector<T> v) noexcept
		{return v*=c;}

	template<class T>
	constexpr Vector<T> operator/(Vector<T> v,T c) noexcept
		{return v/=c;}

	template<class T>
	constexpr Vector<T> operator+(Vector<T> a,Vector<T> b) noexcept
		{return a+=b;}

	template<class T>
	constexpr Vector<T> operator-(Vector<T> a,Vector<T> b) noexcept
		{return a-=b;}

	template<class T>
	constexpr T dot(Vector<T> a,Vector<T> b)
		{
		auto temp=a.data()*b.data();
		return temp[0] + temp[1] + temp[2];
		}

	template<class T>
	constexpr Vector<T> cross(Vector<T> a,Vector<T> b)
		{
		return Vector<T>(a.y()*b.z() - a.z()*b.y()
			,a.z()*b.x() - a.x()*b.z()
			,a.x()*b.y() - a.y()*b.x());
		}

	static_assert(dot(Vector<float>(1.0f,0.0f,0.0f),Vector<float>(0.0f,1.0f,0.0f))==0.0f,"Dot product is broken");
	static_assert(dot(Vector<float>(1.0f,0.0f,0.0f),Vector<float>(1.0f,0.0f,0.0f))==1.0f,"Dot product is broken");

	static_assert(cross(Vector<float>(1.0,0.0f,0.0f),Vector<float>(0.0f,1.0f,0.0f))==Vector<float>(0.0f,0.0f,1.0f)
		,"Cross product is broken");
	}

#endif
