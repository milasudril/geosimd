#include <geosimd/euclidian_space.hpp>

#include <cstdio>

namespace your_project::geom
{
	inline constexpr size_t num_dimensions = 3;

	using scalar = float;
	using the_space = geosimd::euclidian_space<scalar, num_dimensions>;

	using location = the_space::location;
	using displacement = the_space::displacement;
	using direction = the_space::direction;
	using rotation = geosimd::rotation<the_space>;
	using translation = geosimd::translation<the_space>;
	using locrot = geosimd::locrot<the_space>;
	using x = the_space::x;
	using y = the_space::y;
	using z = the_space::z;
	inline constexpr auto origin = geosimd::origin<the_space>();
}

int main()
{
	your_project::geom::location loc{1.0f, 2.0f, 3.0f};
	loc.apply(your_project::geom::rotation{geosimd::rotation_angle{geosimd::turns{0.25}},
		your_project::geom::z{}},
		your_project::geom::location{1.0f, 0.0f, 0.0f}
	);

	auto d = distance(loc, your_project::geom::origin);

	printf("%s %.8e\n", to_string(loc).c_str(), d);
}