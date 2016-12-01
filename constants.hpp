//@	{"targets":[{"name":"constants.hpp","type":"include"}]}

#ifndef GEOSIMD_CONSTANTS_HPP
#define GEOSIMD_CONSTANTS_HPP

#include <cmath>

namespace GeoSIMD
	{
	template<class T>
	constexpr T zero() noexcept
		{return 0;}

	template<>
	constexpr float zero<>() noexcept
		{return 0.0f;}

	template<>
	constexpr double zero<>() noexcept
		{return 0.0;}


	template<class T>
	constexpr T one() noexcept
		{return 1;}

	template<>
	constexpr float one<>() noexcept
		{return 1.0f;}

	template<>
	constexpr double one<>() noexcept
		{return 1.0;}



	template<class T>
	constexpr T two() noexcept
		{return 2;}

	template<>
	constexpr float two<>() noexcept
		{return 2.0f;}

	template<>
	constexpr double two<>() noexcept
		{return 2.0;}



	template<class T>
	constexpr T pi() noexcept;

	template<>
	constexpr float pi<>() noexcept
		{return std::acos(-1.0f);}

	template<>
	constexpr double pi<>() noexcept
		{return std::acos(-1.0);}
	}

#endif
