#ifndef GEOSIMD_STORAGE_HPP
#define GEOSIMD_STORATE_HPP

namespace GeoSIMD
	{
	template<class T>
	using vec4_t __attribute__ ((vector_size (4*sizeof(T))))=T;
	}

#endif