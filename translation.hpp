//@	{"targets":[{"name":"translation.hpp","type":"include"}]}

#ifndef GEOSIMD_TRANSLATION_HPP
#define GEOSIMD_TRANSLATION_HPP

#include "vector.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Translation
		{
		public:
			constexpr Translation():
				m_data(mat4_t<T>::identity())
				{}

			constexpr Translation(Vector<T> offset):m_data(init(offset))
				{}

			constexpr const mat4_t<T>& matrix() const noexcept
				{return m_data;}

			constexpr const T* data() const noexcept
				{return m_data.data();}

			Translation& translate(Vector<T> offset) noexcept
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(3)=offset.data();
				R.column(3)[3]=one<T>();
				m_data*=R;
				return *this;
				}

			constexpr bool operator==(const Translation& rot) noexcept
				{return m_data==rot.m_data;}

		private:
			mat4_t<T> m_data;
			static mat4_t<T> init(Vector<T> offset)
				{
				mat4_t<T> R=mat4_t<T>::identity();
				auto temp=offset.data();
				temp[3]=one<T>();
				R.column(3)=temp;
				return R;
				}
		};

	template<class T>
	Translation<T> translate(Translation<T> R,Vector<T> offset) noexcept
		{return R.translate(offset);}

	template<class T>
	Translation<T> translate(Vector<T> offset) noexcept
		{return Translation<T>(offset);}
	}

#endif
