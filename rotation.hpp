//@	{"targets":[{"name":"rotation.hpp","type":"include"}]}

#ifndef GEOSIMD_ROTATION_HPP
#define GEOSIMD_ROTATION_HPP

#include "angle.hpp"
#include "mat4.hpp"
#include "axis.hpp"
#include "quaternion.hpp"

namespace GeoSIMD
	{
	template<class T>
	class Rotation
		{
		public:
			constexpr Rotation():
				m_data(mat4_t<T>::identity())
				{}

			Rotation(Quaternion q) noexcept
				{
				auto n=1.0f/sqrt(length2(q));
				q*=n;
				m_data.column(0)=vec4_t<T>{1.0f - 2.0f*q.y};
				}

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

			constexpr const mat4_t<T>& matrix() const noexcept
				{return m_data;}

			constexpr const T* data() const noexcept
				{return m_data.data();}

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
				R.column(0)=vec4_t<T>{one<T>(),zero<T>(),zero<T>(),zero<T>()};
				R.column(1)=vec4_t<T>{zero<T>(),cos<T>(angle),sin<T>(angle),zero<T>()};
				R.column(2)=vec4_t<T>{zero<T>(),-sin<T>(angle),cos<T>(angle),zero<T>()};
				return R;
				}

			template<class U>
			static mat4_t<T> init_y(Angle<U> angle)
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=vec4_t<T>{cos<T>(angle),zero<T>(),-sin<T>(angle),zero<T>()};
				R.column(1)=vec4_t<T>{zero<T>(),one<T>(),zero<T>(),zero<T>()};
				R.column(2)=vec4_t<T>{sin<T>(angle),zero<T>(),cos<T>(angle),zero<T>()};
				return R;
				}

			template<class U>
			static mat4_t<T> init_z(Angle<U> angle)
				{
				mat4_t<T> R(mat4_t<T>::identity());
				R.column(0)=vec4_t<T>{cos<T>(angle),sin<T>(angle),zero<T>(),zero<T>()};
				R.column(1)=vec4_t<T>{-sin<T>(angle),cos<T>(angle),zero<T>(),zero<T>()};
				R.column(2)=vec4_t<T>{zero<T>(),zero<T>(),one<T>(),zero<T>()};
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
