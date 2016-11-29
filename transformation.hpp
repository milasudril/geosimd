#ifndef GEOSIMD_TRANSFORMATION_HPP
#define GEOSIMD_TRANSFORMATION_HPP

#include "angle.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Transformation
		{
		public:
			constexpr explicit Transformation():
				m_data{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}
				{}

			constexpr const vec4_t<T>& data() const noexcept
				{return m_data;}

			template<class U>
			constexpr Tranformation& rotateX(Angle<U> angle) noexcept
				{
				vec4_t<T> matrix_temp[4]=
					{
					 {1,0,0,0}
					,{0,angle.cos(),angle.sin(),0,0}
					,{0,-angle.sin(),angle.cos(),0,0}
					,{0,0,0,1}
					};
				return *this;
				}

		private:
			vec4_t<T> m_data[4];
		};
	}

#endif
