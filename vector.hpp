#ifndef GEOSIMD_VECTOR_HPP
#define GEOSIMD_VECTOR_HPP

#include "storage.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Vector
		{
		public:
			explicit Vector(T x,T y,T z):m_data{x,y,z,0}
				{}

			T x() const noexcept
				{return m_data[0];}

			T& x() noexcept
				{return m_data[0];}

			T y() const noexcept
				{return m_data[1];}

			T& y() noexcept
				{return m_data[1];}

			T z() const noexcept
				{return m_data[2];}

			T& z() noexcept
				{return m_data[2];}

			Vector& operator*=(T c) noexcept
				{
				m_data*=c;
				return *this;
				}

			Vector& operator/=(T c) noexcept
				{
				m_data/=c;
				return *this;
				}

			Vector& operator+=(Vector v) noexcept
				{
				m_data+=v;
				return *this;
				}

			Vector& operator-=(Vector v) noexcept
				{
				m_data-=v;
				return *this
				}
		private:
			vec4_t<T> m_data;
		};

	template<class T>
	inline Vector<T> operator*(T c,Vector<T> v) noexcept
		{return v*=c;}

	template<class T>
	inline Vector<T> operator/(Vector<T>,T c) noexcept
		{return v/=c;}

	template<class T>
	inline Vector<T> operator+(Vector<T> a,Vector<T> b) noexcept
		{return a+=b;}

	template<class T>
	inline Vector<T> operator-(Vector<T> a,Vector<T> b) noexcept
		{return a-=b;}

	T dot(Vector<T> a,Vector<T> b)
		{
		a.m_data*=b.m_data;
		return a[0] + a[1] + a[2] + a[3];
		}

	template<class T>
	Vector<T> cross(Vector<T> a,Vector<T> b)
		{
		return Vector<T>(a.y()*b.z() - a.z()*b.y()
			,a.z()*b.x() - a.x()*b.z()
			,a.z()*b.y() - a.y()*b.x());
		}
	}

#endif
