//@	{"targets":[{"name":"transformation.hpp","type":"include"}]}

#ifndef GEOSIMD_TRANSFORMATION_HPP
#define GEOSIMD_TRANSFORMATION_HPP

namespace GeoSIMD
	{
	template<class T>
	class Transformation
		{
		public:
			constexpr Transformation():
				m_data(mat4_t<T>::identity())
				{}

			template<class U>
			constexpr explicit Transformation(const U& R):m_data(R.data())
				{}

			constexpr const mat4_t<T>& data() const noexcept
				{return m_data;}

			template<class U>
			Transformation& push(const U& R) noexcept
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
