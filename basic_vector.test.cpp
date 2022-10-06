//@	{"target":{"name":"basic_vector.test"}}

#include "./basic_vector.hpp"

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

namespace geosimd_test
{
	struct my_vector_space
	{
		using vector_type = geosimd::vec4i32_t;
		using scalar_type = int;
	};

	static_assert(geosimd::vector_space<my_vector_space>);
	static_assert(geosimd::vector<geosimd::basic_vector<my_vector_space>, int>);
}