//@	{"targets":[{"name":"vector.hpp","type":"include"}]}

#ifndef GEOSIMD_VECTOR_HPP
#define GEOSIMD_VECTOR_HPP

#include "vectortype.hpp"
#include "constants.hpp"
#include "rotation.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Vector;

	template<class T>
	Vector<T> transform(Vector<T> v,const Rotation<T>& R) noexcept;

	template<class T>
	class Vector
		{
		public:
			constexpr explicit Vector(T x,T y,T z) noexcept:m_data{x,y,z,zero<T>()}
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
				m_data*=vec4_t<T>{c,c,c,c};
				return *this;
				}

			constexpr Vector& operator/=(T c) noexcept
				{
				auto temp=one<T>()/c;
				m_data*=vec4_t<T>{temp,temp,temp,temp};
				return *this;
				}

			constexpr Vector& operator+=(Vector v) noexcept
				{
				m_data+=v.m_data;
				return *this;
				}

			constexpr Vector& operator-=(Vector v) noexcept
				{
				m_data-=v.m_data;
				return *this;
				}

			constexpr bool operator==(Vector v) const noexcept
				{
                return m_data[0]==v.m_data[0]
                  	&& m_data[1]==v.m_data[1]
					&& m_data[2]==v.m_data[2];
                }

			constexpr T dot(Vector v) const noexcept
				{
				auto temp=m_data*v.m_data;
				return temp[0] + temp[1] + temp[2];
				}

			constexpr vec4_t<T> data() const noexcept
				{return m_data;}

		protected:
			Vector(){}
			vec4_t<T> m_data;

			friend Vector<T> transform<>(Vector<T> v,const Rotation<T>& R) noexcept;
		};

#ifdef __SSE__
      
	constexpr Vector<float> operator""_Vf(long double val)
		{return Vector<float>(val,val,val);}

	constexpr Vector<float> operator""_xf(long double val)
		{return Vector<float>(val,0,0);}
      
	constexpr Vector<float> operator""_yf(long double val)
		{return Vector<float>(0,val,0);}

	constexpr Vector<float> operator""_zf(long double val)
		{return Vector<float>(0,0,val);}
#endif

#ifdef __AVX__
	constexpr Vector<double>
	operator""_V(long double val)
		{return Vector<double>(val,val,val);}
      
	constexpr Vector<double>
	operator""_x(long double val)
		{return Vector<double>(val,0,0);}
      
	constexpr Vector<double>
	operator""_y(long double val)
		{return Vector<double>(0,val,0);}

	constexpr Vector<double>
	operator""_z(long double val)
		{return Vector<double>(0,0,val);}
#endif


#ifdef __SSE2__      
	constexpr Vector<int> operator""_V(unsigned long long int val)
		{return Vector<int>(val,val,val);}
      
	constexpr Vector<int> operator""_x(unsigned long long int val)
		{return Vector<int>(val,0,0);}
      
	constexpr Vector<int> operator""_y(unsigned long long int val)
		{return Vector<int>(0,val,0);}

	constexpr Vector<int> operator""_z(unsigned long long int val)
		{return Vector<int>(0,0,val);}
#endif

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
	constexpr Vector<T> operator-(Vector<T> a) noexcept
		{return (-one<T>())*a;}

	template<class T>
	constexpr T dot(Vector<T> a,Vector<T> b) noexcept
		{return a.dot(b);}  
	static_assert(dot(1.0_xf,1.0_yf)==0.0f,"Dot product broken");
	static_assert(dot(1.0_xf,1.0_xf)==1.0f,"Dot product broken");

      
	template<class T>
	constexpr Vector<T> cross(Vector<T> a,Vector<T> b)
		{
		return Vector<T>(a.y()*b.z() - a.z()*b.y()
			,a.z()*b.x() - a.x()*b.z()
			,a.x()*b.y() - a.y()*b.x());
		}  
	static_assert(cross(1.0_xf,1.0_yf)==1.0_zf,"Cross product broken");
	static_assert(cross(1.0_yf,1.0_zf)==1.0_xf,"Cross product broken");
	static_assert(cross(1.0_zf,1.0_xf)==1.0_yf,"Cross product broken");
	static_assert(cross(1.0_xf,1.0_xf)==0.0_Vf,"Cross product broken");
	static_assert(cross(1.0_xf,1.0_zf)==-1.0_yf,"Cross product broken");

	template<class T>
	Vector<T> transform(Vector<T> v,const Rotation<T>& R) noexcept
		{
		const auto& R_data=R.data();
		Vector<T> ret;
		for(int k=0;k<4;++k)
			{
			auto row=vec4_t<T>
				{R_data(k,0),R_data(k,1),R_data(k,2),R_data(k,3)};
			ret.m_data[k]=GeoSIMD::dot<T>(v.m_data,row);
			}
		return ret;
		}
	}

#endif