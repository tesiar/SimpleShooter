#ifndef RENDER_H
#define RENDER_H

#include <windows.h>
#include "vec.h"
#include "resources.h"

class Render
{
	RGBTRIPLE *bitmap;
	float *zbuffer;
	BITMAPINFOHEADER bih;
	int width, height;
	void Line(int x1, int y1, int x2, int y2, RGBTRIPLE color);
	void Triangle/*(vec3 p1, vec3 p2, vec3 p3, RGBTRIPLE color);*/(vec3 p1, vec3 p2, vec3 p3, vec2 t1, vec2 t2, vec2 t3, RGBTRIPLE* tex, int h, int w);
public:
	Render(int w, int h);
	void Draw();
	const RGBTRIPLE* GetPixels(){return bitmap;}
	const BITMAPINFOHEADER* GetInfo(){return &bih;}
};

#endif
