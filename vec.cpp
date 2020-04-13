#include "vec.h"
#include <math.h>

vec3::vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

vec3 vec3::operator+(vec3 v)
{
	return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator-(vec3 v)
{
	return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator^(vec3 v)
{
	return vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

vec3 vec3::operator*(float a)
{
	return vec3(x*a, y*a, z*a);
}

float vec3::operator*(vec3 v)
{
	return (x*v.x + y*v.y + z*v.z);
}

void vec3::normilize()
{
	float l = sqrt(x*x + y*y + z*z);
	if(l == 0.) return;
	x /= l;
	y /= l;
	z /= l;
}

vec2::vec2(float _u, float _v)
{
	u = _u;
	v = _v;
}

vec2 vec2::operator+(vec2 _v)
{
	return vec2(u + _v.u, v + _v.v);
}

vec2 vec2::operator-(vec2 _v)
{
	return vec2(u - _v.u, v - _v.v);
}

vec2 vec2::operator*(float a)
{
	return vec2(u*a, v*a);
}

float vec2::operator*(vec2 _v)
{
	return (u*_v.u + v*_v.v);
}

void vec2::normilize()
{
	float l = sqrt(u*u + v*v);
	if(l == 0.) return;
	u /= l;
	v /= l;
}

matrix4::matrix4()
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			m[i][j] = 0.;
	for(int i = 0; i < 4; ++i)
		m[i][i] = 1.;
}

vec3 matrix4::operator*(vec3 v)
{
	vec3 res;
	float t = m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3];
	res.x = (m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3])/t;
	res.y = (m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3])/t;
	res.z = (m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3])/t;
	return res;
}

matrix4 matrix4::operator*(matrix4 mat)
{
	matrix4 res;
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			res.m[i][j] = m[i][0]*mat.m[0][j] + m[i][1]*mat.m[1][j] + m[i][2]*mat.m[2][j] + m[i][3]*mat.m[3][j];
	return res;
}

void matrix4::Scale(float a)
{
	for(int i = 0; i < 3; ++i)
		m[i][i] = a;
}

void matrix4::RotateX(float angle)
{
	angle = angle/180.*3.1415;
	m[1][1] = cos(angle);
	m[2][2] = cos(angle);
	m[1][2] = -sin(angle);
	m[2][1] = sin(angle);
}

void matrix4::RotateY(float angle)
{
	angle = angle/180.*3.1415;
	m[0][0] = cos(angle);
	m[2][2] = cos(angle);
	m[0][2] = -sin(angle);
	m[2][0] = sin(angle);
}

void matrix4::RotateZ(float angle)
{
	angle = angle/180.*3.1415;
	m[0][0] = cos(angle);
	m[1][1] = cos(angle);
	m[0][1] = -sin(angle);
	m[1][0] = sin(angle);
}

void matrix4::Persp()
{
	m[3][2] = -0.2;
}
