//@	{
//@	"targets":[{"name":"test","type":"application","cxxoptions":{"cflags_extra":["-fast-math","march=native"],"cxxversion_min":201402}}]
//@	}

#include "direction.hpp"
#include "point.hpp"
#include <cstdio>
#include <cassert>

using namespace GeoSIMD;

void print(const mat4_t<double>& m,int line)
	{
	printf("%d:\n",line);
	for(int row=0;row<4;++row)
		{
		for(int col=0;col<4;++col)
			{printf("%.7g ",m(row,col));}
		putchar('\n');
		}
	putchar('\n');
	}

void print(const vec4_t<double>& m,int line)
	{
	printf("%d: ",line);
	putchar('(');
	for(int k=0;k<3;++k)
		{printf("%.7g, ",m[k]);}
	printf("%.7g)\n\n",m[3]);
	}

int main()
	{
	Rotation<double> rot_a;
	Rotation<double> rot_b;
	rot_a.rotateX(90.0_deg);

	print(rot_a.data(),__LINE__);

	rot_a.rotateX(-90.0_deg);
	print(rot_a.data(),__LINE__);
	assert(rot_a==rot_b);


	auto e1=transform(x<double>(),rotateZ(rot_a,90.0_deg));
	print(e1.data(),__LINE__);

	auto P=transform(origin<double>(),translate(Translation<double>(),1.0_x));
	P=transform(P,rotateZ<double>(90.0_deg));
	print(P.data(),__LINE__);

	auto T_tot=Transformation<double>(rotateZ<double>(0.25_r))
		.append(translate(1.0_x));
	print(T_tot.data(),__LINE__);

	auto P2=transform(origin<double>(),T_tot);
	print(P2.data(),__LINE__);

	return 0;
	}
