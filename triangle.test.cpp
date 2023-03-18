//@	{"target":{"name":"triangle.test"}}

#include "./triangle.hpp"

#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"


TESTCASE(geosimd_triangle_project_from_above)
{
	using loc = geosimd::euclidian_space<float, 3>::location;
	using vec = geosimd::euclidian_space<float, 3>::displacement;

	auto const origin = loc{1.0f, 2.0f, 4.0f};

	geosimd::triangle T{
		origin + 16.0f*vec{0.0f, 0.25f, 0.0f},
		origin + 16.0f*vec{2.0f, 0.0f, 0.0f},
		origin + 16.0f*vec{1.5f, 1.0f, 1.0f}
	};

	using scanline = std::array<float, 33>;
	using image = std::array<scanline, 17>;

	image img{};

	project_from_above(T, [origin](loc p, image& img){
		printf("%s\n", to_string(p - origin).c_str());
		auto v = p - origin;
		img[static_cast<size_t>(v[1])][static_cast<size_t>(v[0])] = p[2];
	}, std::ref(img));

	for(size_t k = 0; k != 17; ++k)
	{
		for(size_t l = 0; l != 33; ++l)
		{
			if(img[k][l] > 0.5f)
			{
				putchar('*');
			}
			else
			{
				putchar(' ');
			}
		}
		putchar('\n');
	}
}