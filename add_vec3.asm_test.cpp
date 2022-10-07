#include "./basic_vector.hpp"
#include "./vec_t.hpp"

namespace geosimd_test
{
	struct my_vector_space_3d
	{
		using vector_type = geosimd::vec4i32_t;
		using scalar_type = int;
		using enable_homogenous_coordinates_t = void;
	};

	using vec3 = geosimd::basic_vector<my_vector_space_3d>;

	static_assert(sizeof(vec3) == 16);

	using vec4_raw = geosimd::native_vector<int, 4>;

	GEOSIMD_FORCE_OPT geosimd::vec4i32_t add(geosimd::vec4i32_t a, geosimd::vec4i32_t b)
	{ return a + b; }

	GEOSIMD_FORCE_OPT vec3 add(vec3 a, vec3 b)
	{ return a + b; }

	GEOSIMD_FORCE_OPT vec4_raw add(vec4_raw a, vec4_raw b)
	{ return a + b; }
}

