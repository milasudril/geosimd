//@	{"targets":[{"name":"frustum.hpp","type":"include"}]}

#ifndef GEOSIMD_FRUSTUM_HPP
#define GEOSIMD_FRUSTUM_HPP

#include "point.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Frustum
		{
		public:
			Frustum(Point<T> min,Point<T> max) noexcept
				{
				auto size=max - min;
				auto mid=centroid({min,max});

				m_data[0]=vec4_t<T>
					{
					 two<T>()*min.z()/size.x()
					,zero<T>()
					,zero<T>()
					,zero<T>()
					};

				m_data[1]=vec4_t<T>
					{
					 zero<T>()
					,two<T>()*min.z()/size.y()
					,zero<T>()
					,zero<T>()
					}

				m_data[2]=vec4_t<T>
					{
					 two<T>()*mid.x()/size.x()
					,two<T>()*mid.y()/size.y()
					,-two<T>()*mid.z()/size.z()
					,-one<T>()
					};

				m_data[3]=vec4_t<T>
					{
					 zero<T>()
					,zero<T>()
					,zero<T>()
					,-two<T>()*max.z()*min.z()/size.z()
					};
				}

			const mat4_t<T>& data() const noexcept
				{return m_data;}

			bool operator==(const Frustum& frst) noexcept
				{return m_data==frst.m_data;}

		private:
			mat4_t<T> m_data;
		};
	}

#endif
