//@	{
//@	"targets":[{"name":"test","type":"application","cxxoptions":{"cflags_extra":["march=native","-fast-math"],"cxxversion_min":201402}}]
//@	}

#include "angle.hpp"
#include "point.hpp"
#include "rotation.hpp"
#include <cstdio>
#include <cassert>

using namespace GeoSIMD;

void matrixPrint(const mat4_t<float>& m)
	{
	for(int row=0;row<4;++row)
		{
		for(int col=0;col<4;++col)
			{printf("%.7g ",m(row,col));}
		putchar('\n');
		}
	}

int main()
	{
	Rotation<float> rot_a;
	Rotation<float> rot_b;
	rot_a.rotateX(90.0_degf);

	matrixPrint(rot_a.data());

	rot_a.rotateX(-90.0_degf);
	matrixPrint(rot_a.data());
	assert(rot_a==rot_b);
	return 0;
	}