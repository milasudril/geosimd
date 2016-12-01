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
			Frustum(Point<T> min,Point<T> max) noexcept:m_data(init(min,max))
				{}

			template<class U>
			Frustum(T z_min,T z_max,Angle<U> fov_x,T view_ratio) noexcept
				{
				auto tan_theta=tan<float>(fov_x/two<U>());
				auto x_max=tan_theta*z_min;
				auto y_max=y_max/view_ratio;
				auto min=Point<T>(-x_max,-y_max,z_min);
				auto max=Point<T>(x_max,y_max,z_max);
				m_data=init(min,max);
				}

			template<class U>
			Frustum(T z_min,T z_max,T view_ratio,Angle<U> fov_y) noexcept
				{
				auto tan_theta=tan<float>(fov_y/two<U>());
				auto y_max=tan_theta*z_min;
				auto x_max=y_max*view_ratio;
				auto min=Point<T>(-x_max,-y_max,z_min);
				auto max=Point<T>(x_max,y_max,z_max);
				m_data=init(min,max);
				}

			const mat4_t<T>& data() const noexcept
				{return m_data;}

			bool operator==(const Frustum& frst) noexcept
				{return m_data==frst.m_data;}

		private:
			mat4_t<T> m_data;
			static mat4_t<T> init(Point<T> min,Point<T> max)
				{
				mat4_t<T> ret;
				auto size=max - min;
				auto mid=centroid({min,max});

				ret.column(0)=vec4_t<T>
					{
					 two<T>()*min.z()/size.x()
					,zero<T>()
					,zero<T>()
					,zero<T>()
					};

				ret.column(1)=vec4_t<T>
					{
					 zero<T>()
					,two<T>()*min.z()/size.y()
					,zero<T>()
					,zero<T>()
					};

				ret.column(2)=vec4_t<T>
					{
					 two<T>()*mid.x()/size.x()
					,two<T>()*mid.y()/size.y()
					,-two<T>()*mid.z()/size.z()
					,-one<T>()
					};

				ret.column(3)=vec4_t<T>
					{
					 zero<T>()
					,zero<T>()
					,-two<T>()*max.z()*min.z()/size.z()
					,zero<T>()
					};

				return ret;
				}
		};
	}

#endif
