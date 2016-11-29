//@	{"targets":[{"name":"transformation.hpp","type":"include"}]}

#ifndef GEOSIMD_TRANSFORMATION_HPP
#define GEOSIMD_TRANSFORMATION_HPP

#include "translation.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Transformation
		{
		public:
			constexpr explicit Transformation():
				m_data(mat4_t<T>::identity())
				{}

			template<class U>
			Transformation(const U& R):Transformation()
				{append(R);}

			constexpr const mat4_t<T>& data() const noexcept
				{return m_data;}

			template<class U>
			Transformation& append(const U& R) noexcept
				{
				m_data*=R.data();
				return *this;
				}

			constexpr bool operator==(const Transformation<T>& rot) noexcept
				{return m_data==rot.m_data;}

		private:
			mat4_t<T> m_data;
		};
	}

#endif
