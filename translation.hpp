//@	{"targets":[{"name":"translation.hpp","type":"include"}]}

#ifndef GEOSIMD_TRANSLATION_HPP
#define GEOSIMD_TRANSLATION_HPP

#include "mat4.hpp"
#include "vector.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Translation
		{
		public:
			constexpr explicit Translation():
				m_data(mat4_t<T>::identity())
				{}

			constexpr const mat4_t<T>& data() const noexcept
				{return m_data;}

			Translation& translate(Vector<T> offset) noexcept
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(3)=offset.data();
				m_data*=R;
				return *this;
				}

			constexpr bool operator==(const Translation& rot) noexcept
				{return m_data==rot.m_data;}

		private:
			mat4_t<T> m_data;
		};

	template<class T>
	Translation<T> translate(Rotation<T> R,Vector<T> offset) noexcept
		{return R.translate(offset);}
	}

#endif
