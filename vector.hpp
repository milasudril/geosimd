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
	}

#endif
