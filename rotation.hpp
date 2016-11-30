//@	{"targets":[{"name":"rotation.hpp","type":"include"}]}

#ifndef GEOSIMD_ROTATION_HPP
#define GEOSIMD_ROTATION_HPP

#include "angle.hpp"
#include "mat4.hpp"

namespace GeoSIMD
	{
	struct X
		{};

	struct Y
		{};

	struct Z
		{};

	template<class T>
	class Rotation
		{
		public:
			constexpr Rotation():
				m_data(mat4_t<T>::identity())
				{}

			template<class U>
			constexpr Rotation(Angle<U> angle,X) noexcept:
				m_data(init_x(angle))
				{}

			template<class U>
			constexpr Rotation(Angle<U> angle,Y) noexcept:
				m_data(init_y(angle))
				{}

			template<class U>
			constexpr Rotation(Angle<U> angle,Z) noexcept:
				m_data(init_z(angle))
				{}

			constexpr const mat4_t<T>& data() const noexcept
				{return m_data;}

			template<class U>
			Rotation& rotateX(Angle<U> angle) noexcept
				{
				m_data*=init_x(angle);
				return *this;
				}

			template<class U>
			Rotation& rotateY(Angle<U> angle) noexcept
				{
				m_data*=init_y(angle);
				return *this;
				}

			template<class U>
			Rotation& rotateZ(Angle<U> angle) noexcept
				{
				m_data*=init_z(angle);
				return *this;
				}

			constexpr bool operator==(const Rotation& rot) noexcept
				{return m_data==rot.m_data;}

			template<class U>
			static Rotation xyz(Angle<U> x,Angle<U> y,Angle<U> z) noexcept
				{return Rotation(x,X()).rotateY(y).rotateZ(z);}

			template<class U>
			static Rotation zyz(Angle<U> z,Angle<U> y,Angle<U> z_prime) noexcept
				{return Rotation(z,Z()).rotateY(y).rotateZ(z_prime);}

		private:
			mat4_t<T> m_data;

			template<class U>
			static mat4_t<T> init_x(Angle<U> angle)
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=GeoSIMD::vec4_t<float>{one<T>(),zero<T>(),zero<T>(),zero<T>()};
				R.column(1)=GeoSIMD::vec4_t<float>{zero<T>(),cos(angle),sin(angle),zero<T>()};
				R.column(2)=GeoSIMD::vec4_t<float>{zero<T>(),-sin(angle),cos(angle),zero<T>()};
				return R;
				}

			template<class U>
			static mat4_t<T> init_y(Angle<U> angle)
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=GeoSIMD::vec4_t<float>{cos(angle),zero<T>(),-sin(angle),zero<T>()};
				R.column(1)=GeoSIMD::vec4_t<float>{zero<T>(),one<T>(),zero<T>(),zero<T>()};
				R.column(2)=GeoSIMD::vec4_t<float>{sin(angle),zero<T>(),cos(angle),zero<T>()};
				return R;
				}

			template<class U>
			static mat4_t<T> init_z(Angle<U> angle)
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=GeoSIMD::vec4_t<float>{cos(angle),sin(angle),zero<T>(),zero<T>()};
				R.column(1)=GeoSIMD::vec4_t<float>{-sin(angle),cos(angle),zero<T>(),zero<T>()};
				R.column(2)=GeoSIMD::vec4_t<float>{zero<T>(),zero<T>(),one<T>(),zero<T>()};
				return R;
				}
		};

	template<class T,class U>
	Rotation<T> rotateX(Rotation<T> R,Angle<U> angle) noexcept
		{return R.rotateX(angle);}

	template<class T,class U>
	Rotation<T> rotateX(Angle<U> angle) noexcept
		{return Rotation<T>(angle,X());}

	template<class T,class U>
	Rotation<T> rotateY(Rotation<T> R,Angle<U> angle) noexcept
		{return R.rotateY(angle);}

	template<class T,class U>
	Rotation<T> rotateY(Angle<U> angle) noexcept
		{return Rotation<T>(angle,Y());}

	template<class T,class U>
	Rotation<T> rotateZ(Rotation<T> R,Angle<U> angle) noexcept
		{return R.rotateZ(angle);}

	template<class T,class U>
	Rotation<T> rotateZ(Angle<U> angle) noexcept
		{return Rotation<T>(angle,Z());}
	}

#endif
