//@	{"targets":[{"name":"point.hpp","type":"include"}]}

#ifndef GEOSIMD_POINT_HPP
#define GEOSIMD_POINT_HPP

#include "vector.hpp"
#include <cassert>

namespace GeoSIMD
	{
	template<class T>
	class Point;

	template<class T>
	Point<T> transform(Point<T> p,const mat4_t<T>& R_data) noexcept;

	template<class T>
	class Point
		{
		public:
			typedef vec4_t<T> Representation;

			constexpr Point() noexcept:m_data{zero<T>(),zero<T>(),zero<T>(),one<T>()}
				{}

			constexpr explicit Point(T x,T y,T z):m_data{x,y,z,one<T>()}
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

			constexpr Point& operator+=(Vector<T> v) noexcept
				{
				m_data+=v.data();
				return *this;
				}

			constexpr Point& operator-=(Vector<T> v) noexcept
				{
				m_data-=v.data();
				return *this;
				}

			constexpr bool operator==(Point v) const noexcept
				{
				return m_data[0]==v.m_data[0]
					&& m_data[1]==v.m_data[1]
					&& m_data[2]==v.m_data[2];
                }

			constexpr Representation data() const noexcept
				{return m_data;}

			template<int N>
			static constexpr Point centroid(const Point(&points)[N]) noexcept
				{
				static_assert(N!=0,"At least one point is needed");
				Point<T> ret;
				for(int k=0;k<N;++k)
					{ret.m_data+=points[k].m_data;}

				ret.m_data/=static_cast<T>(N);
				ret.m_data[3]=one<T>();
				return ret;
				}

			static Point centroid(const Point* begin,const Point* end) noexcept;

		private:
			Representation m_data;

			friend Point<T> transform<>(Point<T> p,const mat4_t<T>& R_data) noexcept;
		};

	template<class T>
	inline constexpr Point<T> origin() noexcept
		{return Point<T>(zero<T>(),zero<T>(),zero<T>());}

	template<class T>
	inline constexpr Point<T> operator+(Point<T> a,Vector<T> b) noexcept
		{return a+=b;}

	template<class T>
	inline constexpr Point<T> operator-(Point<T> a,Vector<T> b) noexcept
		{return a-=b;}

	template<class T>
	inline constexpr Vector<T> operator-(Point<T> a,Point<T> b) noexcept
		{
		Vector<T> ret{};
		ret.m_data=a.data() - b.data();
		return ret;
		}

	template<class T>
	inline constexpr T distance_squared(Point<T> a,Point<T> b) noexcept
		{return length_squared(a-b);}

	static_assert(distance_squared(origin<float>(),Point<float>(1.0f,1.0f,1.0f))==3.0f,"distance broken");

	template<class T>
	inline Point<T> transform(Point<T> p,const mat4_t<T>& R_data) noexcept
		{
		Point<T> ret;
		ret.m_data=R_data*p.m_data;
		return ret;
		}

	template<class T,class U>
	inline Point<T> transform(Point<T> p,const U& u) noexcept
		{return transform(p,u.matrix());}

	template<class T,int N>
	inline constexpr Point<T> centroid(const Point<T>(&points)[N]) noexcept
		{return Point<T>::centroid(points);}

	template<class T>
	Point<T> Point<T>::centroid(const Point<T>* begin,const Point<T>* end) noexcept
		{
		auto N=end - begin;
		assert(N!=0);
		Point<T> ret;
		while(begin!=end)
			{
			ret.m_data+=begin->m_data;
			++begin;
			}
		ret.m_data/=static_cast<T>(N);
		ret.m_data[3]=one<T>();
		return ret;
		}

	template<class T>
	inline Point<T> centroid(const Point<T>* begin,const Point<T>* end) noexcept
		{return Point<T>::centroid(begin,end);}
	}

#endif
