#ifndef GEOSIMD_QUATERNION_HPP
#define GEOSIMD_QUATERNION_HPP

#include "vectortype.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Quaternion
		{
		public:
			explicit Quaternion(float a,float b,float c,float d):
				m_data(a,b,c,d)
				{}

			Quaternion& operator+=(Quaternion q) noexcept
				{
				m_data+=q.m_data;
				return *this;
				}

			Quaternion& operator-=(Quaternion q) noexcept
				{
				m_data-=q.m_data;
				return *this;
				}

			Quaternion& operator*=(T c) noexcept
				{
				m_data*=vec4_t<T>{c,c,c,c};
				return *this;
				}

			Quaternion& operator*=(Quaternion q) noexcept
				{
				auto _a=q.a()*a()
					-q.b()*b()
					-q.c()*c()
					-q.d()*d();

				auto _b=a()*q.b() + b()*q.a() + c()*q.d() - d()*q.c();
				auto _c=a()*q.c() - b()*q.d() + c()*q.a() + d()*q.b();
				auto _d=a()*q.d() + b()*q.c() - c()*q.b() + d()*q.a();

				m_data={_a,_b,_c,_d};
				}

			T a() const noexcept
				{return m_data[0];}

			T b() const noexcept
				{return m_data[1];}

			T c() const noexcept
				{return m_data[2];}

			T d() const noexcept
				{return m_data[3];}

			T length2() const noexcept
				{return dot(m_data,m_data);}

			T w() const noexcept
				{return a();

			T x() const noexcept 
				{return b();}
	
			T y() const noexcept
				{return c();}

			T z() const noexcept
				{return d();}
		

		private:
			vec4_t<T> m_data;
		};

	template<class T>
	inline T length2(Quaternion q) noexcept
		{return q.length2();}
	}

#endif