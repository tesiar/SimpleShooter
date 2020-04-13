#ifndef VEC_H
#define VEC_H

class vec3
{
public:
	float x, y, z;
	vec3(){x = y = z = 0.;}
	vec3(float _x, float _y, float _z);
	vec3 operator+(vec3 v);
	vec3 operator-(vec3 v);
	vec3 operator^(vec3 v);
	vec3 operator*(float a);
	float operator*(vec3 v);
	void normilize();
};

class vec2
{
public:
	float u, v;
	vec2(){u = v = 0.;}
	vec2(float _u, float _v);
	vec2 operator+(vec2 v);
	vec2 operator-(vec2 v);
	vec2 operator*(float a);
	float operator*(vec2 v);
	void normilize();
};

class matrix4
{
	float m[4][4];
public:
	matrix4();
	vec3 operator*(vec3 v);
	matrix4 operator*(matrix4 mat);
	void Scale(float a);
	void ShiftX(float a){m[0][3] = a;}
	void ShiftY(float a){m[1][3] = a;}
	void ShiftZ(float a){m[2][3] = a;}
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Persp();
};

#endif
