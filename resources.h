#ifndef RESOURCES_H
#define RESOURCES_H

#include "vec.h"
#include <vector>
#include <windows.h>

class Model
{
public:
	std::vector<vec3> verts;
	std::vector<int> faces;
	std::vector<vec2> tverts;
	std::vector<int> tfaces;
	RGBTRIPLE* tex;
	int w, h;
	Model(const char* model_name, const char* tex_name);
	BITMAPINFOHEADER* infohead;
};

#endif
