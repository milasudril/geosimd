//@	{
//@	"targets":[{"name":"test","type":"application","cxxoptions":{"cflags_extra":["-fast-math"],"cxxversion_min":201402}}]
//@	}

#include "direction.hpp"
#include "point.hpp"
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
	printf("%.7g)\n\n",m[3]);
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


	auto e1=transform(x<float>(),rotateZ(rot_a,90.0_degf));
	print(rot_a.data());
	print(e1.data());

	auto P=transform(origin<float>(),translate(Translation<float>(),Vector<float>(1.0f,0.0f,0.0f)));
	print(P.data());


	P=transform(P,rotateZ(rot_a,90.0_degf));
	print(P.data());

	auto offset_x=translate(Translation<float>(),1.0_xf);
	auto offset_y=translate(Translation<float>(),1.0_yf);
	auto offset_z=translate(Translation<float>(),1.0_zf);
	auto Tx=Transformation<float>(offset_x);
	print(Tx.data());

	auto Ty=Transformation<float>(offset_y);
	print(Ty.data());

	auto Tz=Transformation<float>(offset_z);
	print(Tz.data());

	auto T_tot=Transformation<float>(rotateZ<float>(90.0_degf))
		.append(translate(1.0_xf));
	print(T_tot.data());

	auto P2=transform(origin<float>(),T_tot);
	print(P2.data());

	return 0;
	}
