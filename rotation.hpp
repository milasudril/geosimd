//@	{"targets":[{"name":"rotation.hpp","type":"include"}]}

#ifndef GEOSIMD_ROTATION_HPP
#define GEOSIMD_ROTATION_HPP

#include "angle.hpp"
#include "mat4.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Rotation
		{
		public:
			constexpr explicit Rotation():
				m_data(mat4_t<T>::identity())
				{}

			constexpr const mat4_t<T>& data() const noexcept
				{return m_data;}

			template<class U>
			Rotation& rotateX(Angle<U> angle) noexcept
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=GeoSIMD::vec4_t<float>{one<T>(),zero<T>(),zero<T>(),zero<T>()};
				R.column(1)=GeoSIMD::vec4_t<float>{zero<T>(),cos(angle),sin(angle),zero<T>()};
				R.column(2)=GeoSIMD::vec4_t<float>{zero<T>(),-sin(angle),cos(angle),zero<T>()};
				m_data*=R;
				return *this;
				}

			template<class U>
			Rotation& rotateY(Angle<U> angle) noexcept
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=GeoSIMD::vec4_t<float>{cos(angle),zero<T>(),-sin(angle),zero<T>()};
				R.column(1)=GeoSIMD::vec4_t<float>{zero<T>(),one<T>(),zero<T>(),zero<T>()};
				R.column(2)=GeoSIMD::vec4_t<float>{sin(angle),zero<T>(),cos(angle),zero<T>()};
				m_data*=R;
				return *this;
				}

			template<class U>
			Rotation& rotateZ(Angle<U> angle) noexcept
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=GeoSIMD::vec4_t<float>{cos(angle),sin(angle),zero<T>(),zero<T>()};
				R.column(1)=GeoSIMD::vec4_t<float>{-sin(angle),cos(angle),zero<T>(),zero<T>()};
				R.column(2)=GeoSIMD::vec4_t<float>{zero<T>(),zero<T>(),one<T>(),zero<T>()};
				m_data*=R;
				return *this;
				}

			constexpr bool operator==(const Rotation& rot) noexcept
				{return m_data==rot.m_data;}

			template<class U>
			static Rotation xyz(Angle<U> x,Angle<U> y,Angle<U> z) noexcept
				{return Rotation().rotateX(x).rotateY(y).rotateZ(z);}

			template<class U>
			static Rotation zyz(Angle<U> z,Angle<U> y,Angle<U> z_prime) noexcept
				{return Rotation().rotateZ(z).rotateY(y).rotateZ(z_prime);}

		private:
			mat4_t<T> m_data;
		};

	template<class T,class U>
	Rotation<T> rotateX(Rotation<T> R,Angle<U> angle) noexcept
		{return R.rotateX(angle);}

	template<class T,class U>
	Rotation<T> rotateY(Rotation<T> R,Angle<U> angle) noexcept
		{return R.rotateY(angle);}

	template<class T,class U>
	Rotation<T> rotateZ(Rotation<T> R,Angle<U> angle) noexcept
		{return R.rotateZ(angle);}
	}

#endif
