#ifndef GEOSIMD_INLINE_HPP
#define GEOSIMD_INLINE_HPP

#ifdef COVERAGE_BUILD
	#define GEOSIMD_FORCE_OPT
	#define GEOSIMD_INLINE
	#define GEOSIMD_FLATTEN
	#define GEOSIMD_INLINE_OPT

	#include <cstddef>
	#include <type_traits>

	namespace geosimd::codecov
	{
		inline char const* last_file;
		inline size_t last_line;

		constexpr void function_called(char const* file, size_t line)
		{
			if(!std::is_constant_evaluated())
			{
				last_file = file;
				last_line = line;
			}
		}
	};

#else
	#define GEOSIMD_FORCE_OPT [[gnu::optimize(3)]] [[gnu::nocf_check]]
	#define GEOSIMD_INLINE [[gnu::always_inline]]
	#define GEOSIMD_FLATTEN [[gnu::flatten]]
	#define GEOSIMD_INLINE_OPT GEOSIMD_FORCE_OPT GEOSIMD_INLINE

	#include <cstddef>

	namespace geosimd::codecov
	{
		constexpr void function_called(char const*, size_t) {}
	};

#endif

#endif