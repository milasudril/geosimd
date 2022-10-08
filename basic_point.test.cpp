//@	{"target":{"name":"basic_point.test"}}

#include "./basic_point.hpp"

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

namespace geosimd
{
	struct my_vector_space_3d:public geosimd::hilbert_space<geosimd::vec4i32_t>
	{
		using enable_homogenous_coordinates_t = void;
		using point_type = geosimd::vec4i32_t;
	};

	static_assert(geosimd::affine_space<my_vector_space_3d>);
	static_assert(geosimd::point<geosimd::basic_point<my_vector_space_3d>>);

	struct my_vector_space_1d
	{
		using vector_type = intptr_t;
		using scalar_type = intptr_t;
		using point_type = std::byte*;
	};

	static_assert(geosimd::affine_space<my_vector_space_1d>);
	static_assert(geosimd::point<geosimd::basic_point<my_vector_space_1d>>);
}