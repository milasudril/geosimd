#include "./euclidian_space.hpp"

auto apply(geosimd::location<float, 3> loc, geosimd::locrot<geosimd::euclidian_space<float, 3>> const& t)
{
	return loc.apply(t, geosimd::location<float, 3>{});
}