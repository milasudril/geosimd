#ifndef GEOSIMD_MAT4_HPP
#define GEOSIMD_MAT4_HPP

#include "storage.hpp"
#include "constants.hpp"

namespace GeoSIMD
	{
	template<class T>
	class mat4_t
		{
		public:
			constexpr T& operator()(int row,int col) noexcept
				{return cols[col][row];}
		  
			constexpr T operator()(int row,int col) const noexcept
				{return cols[col][row];}
		  
			constexpr vec4_t<T>& column(int col) noexcept
				{return cols[col];}
		  
			constexpr mat4_t& operator+=(const mat4_t& m) noexcept
				{
				for(int k=0;k<4;++k)
					{cols[k]+=m.cols[k];}
				return *this;
				}
		  
			constexpr mat4_t& operator-=(const mat4_t& m) noexcept
				{
				for(int k=0;k<4;++k)
					{cols[k]-=m.cols[k];}
				return *this;
				}
		  
			constexpr mat4_t& operator*=(T c) noexcept
				{
				for(int k=0;k<4;++k)
					{cols[k]*=c;}
				return *this;
				}
		  
			mat4_t& operator*=(const mat4_t& c) noexcept
				{
				for(int k=0;k<4;++k)
					{
					vec4_t<T> row{cols[0][k],cols[1][k],cols[2][k],cols[3][k]};
					for(int l=0;l<4;++l)
						{cols[l][k]=dot<T>(row,c.cols[l]);}
					}
				return *this;
				}
		  
			static constexpr mat4_t identity() noexcept
				{
				mat4_t ret{};
				ret.cols[0]=vec4_t<T>{one<T>(),zero<T>(),zero<T>(),zero<T>()};
				ret.cols[1]=vec4_t<T>{zero<T>(),one<T>(),zero<T>(),zero<T>()};
				ret.cols[2]=vec4_t<T>{zero<T>(),zero<T>(),one<T>(),zero<T>()};
				ret.cols[3]=vec4_t<T>{zero<T>(),zero<T>(),zero<T>(),one<T>()};
				return ret;
				}

			constexpr bool operator==(const mat4_t& m) noexcept
				{
				for(int k=0;k<4;++k)
					{
					for(int l=0;l<4;++l)
						{
						if(cols[k][l]!=m.cols[k][l])
							{return 0;}
						}
					}
				return 1;
				}

		  
		private:
			vec4_t<T> cols[4];
		};

	  
	template<class T>
	mat4_t<T> operator*(T c,mat4_t<T> A)
		{return A*=c;}
	  
	template<class T>
	mat4_t<T> operator-(mat4_t<T> A,const mat4_t<T>& B)
		{return A-=B;}

	}
#endif
