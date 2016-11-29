//@	{
//@	"targets":[{"name":"test","type":"application","cxxoptions":{"cflags_extra":["-fast-math"],"cxxversion_min":201402}}]
//@	}

#include "direction.hpp"
#include <cstdio>
#include <cassert>

using namespace GeoSIMD;

void print(const mat4_t<float>& m)
	{
	for(int row=0;row<4;++row)
		{
		for(int col=0;col<4;++col)
			{printf("%.7g ",m(row,col));}
		putchar('\n');
		}
	putchar('\n');
	}

void print(const vec4_t<float>& m)
	{
	putchar('(');
	for(int k=0;k<3;++k)
		{printf("%.7g, ",m[k]);}
	printf("%.7g)\n",m[3]);
	}

int main()
	{
	Rotation<float> rot_a;
	Rotation<float> rot_b;
	rot_a.rotateX(90.0_degf);

	print(rot_a.data());

	rot_a.rotateX(-90.0_degf);
	print(rot_a.data());
	assert(rot_a==rot_b);


	auto e1=x<float>();
	e1.transform(rot_a.rotateZ(90.0_degf));
	print(rot_a.data());
	print(e1.data());
	return 0;
	}