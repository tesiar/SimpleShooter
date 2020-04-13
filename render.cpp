#include "render.h"
#include <cstring>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <limits>

std::ofstream logger("log.txt");

Model cube("Grass_Block.obj", "Grass_Block_TEX.bmp");
Model cube2("Grass_Block.obj", "Grass_Block_TEX.bmp");
//Model cube("african_head.obj", "Grass_Block_TEX.bmp");

Render::Render(int w, int h)
{
	bitmap = new RGBTRIPLE[w*h];
	zbuffer = new float[w*h];
	width = w;
	height = h;
	memset(&bih, 0, sizeof(bih));
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = w*h*3;
	bih.biWidth = w;
	bih.biHeight = -h;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
}

void Render::Line(int x1, int y1, int x2, int y2, RGBTRIPLE color)
{
	bool steep = false;
    if (abs(x1-x2)<abs(y1-y2)) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }
    
    if (x1>x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int dx = x2-x1;
    int dy = y2-y1;
    int derror2 = abs(dy)*2;
    int error2 = 0;
    int y = y1;
    for (int x=x1; x<=x2; x++) {
        if (steep) {
        	if(!((x<0)||(x>(height-1))||(y<0)||(y>(width-1)))) bitmap[x*width + y] = color;
        } else {
        	if(!((x<0)||(x>(width-1))||(y<0)||(y>(height-1)))) bitmap[y*width + x] = color;
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (y2>y1?1:-1);
            error2 -= dx*2;
        }
    }
}

float z_init = -std::numeric_limits<float>::infinity();

void Render::Draw()
{
	memset(bitmap, 0, width*height*3);
	for(int i = 0; i < height; ++i)
		for(int j = 0; j < width; ++j)
			zbuffer[i*width + j] = z_init;
	matrix4 s;
	s.Scale(100.);
	s.ShiftX(400.);
	s.ShiftY(400.);
	matrix4 r, r2, p;
	static float rot = 350.;
	r.RotateY(rot);
	r2.RotateX(rot);
	p.Persp();
	for(int i = 0; i < cube.faces.size()/3; ++i)
	{
		//for(int j = 0; j < 3; ++j)
		//{
			vec3 v1 = s*r*r2*p*cube.verts[cube.faces[3*i]];
			vec3 v2 = s*r*r2*p*cube.verts[cube.faces[3*i+1]];
			vec3 v3 = s*r*r2*p*cube.verts[cube.faces[3*i+2]];
			vec3 n = (v3-v1)^(v2-v1);
			n.normilize();
			vec3 light(0., 0., 1.);
			float p = n*light;
			if(p>0.)
			{
				RGBTRIPLE color;
				color.rgbtBlue = color.rgbtGreen = color.rgbtRed = (int)(255*p);
				Triangle(v1, v2, v3, cube.tverts[cube.faces[3*i]], cube.tverts[cube.faces[3*i+1]], cube.tverts[cube.faces[3*i+2]], cube.tex, cube.h, cube.w);
			}
			//Line(v1.x, v1.y, v2.x, v2.y, {255, 255, 255});
		//}
	}
	s.Scale(20.);
	s.ShiftX(150.);
	s.ShiftY(150.);
	s.ShiftZ(500.);
	r.RotateY(-rot);
	r2.RotateX(-rot);
	for(int i = 0; i < cube2.faces.size()/3; ++i)
	{
		//for(int j = 0; j < 3; ++j)
		//{
			vec3 v1 = s*r*r2*p*cube2.verts[cube2.faces[3*i]];
			vec3 v2 = s*r*r2*p*cube2.verts[cube2.faces[3*i+1]];
			vec3 v3 = s*r*r2*p*cube2.verts[cube2.faces[3*i+2]];
			vec3 n = (v3-v1)^(v2-v1);
			n.normilize();
			vec3 light(0., 0., 1.);
			float p = n*light;
			if(p>0.)
			{
				RGBTRIPLE color;
				color.rgbtBlue = color.rgbtGreen = color.rgbtRed = (int)(255*p);
				//Triangle(v1, v2, v3, color);
				Triangle(v1, v2, v3, cube2.tverts[cube2.faces[3*i]], cube2.tverts[cube2.faces[3*i+1]], cube2.tverts[cube2.faces[3*i+2]], cube2.tex, cube2.h, cube2.w);
			}
			//Line(v1.x, v1.y, v2.x, v2.y, {255, 255, 255});
		//}
	}
	rot += 1;
	if(rot>360) rot = 0;
	//logger << rot << std::endl << std::flush;
}

void Render::Triangle/*(vec3 p1, vec3 p2, vec3 p3, RGBTRIPLE color)*/(vec3 p1, vec3 p2, vec3 p3, vec2 t1, vec2 t2, vec2 t3, RGBTRIPLE* tex, int h, int w)
{
	if (p1.y==p2.y && p1.y==p3.y) return;
    if (p1.y>p2.y){ std::swap(p1, p2); std::swap(t1, t2);}
    if (p1.y>p3.y){ std::swap(p1, p3); std::swap(t1, t3);}
    if (p2.y>p3.y){ std::swap(p2, p3); std::swap(t2, t3);}
    int total_height = (int)p3.y-(int)p1.y;
    for (int i=0; i<total_height; i++) {
        bool second_half = i>((int)p2.y-(int)p1.y) || (int)p2.y==(int)p1.y;
        int segment_height = second_half ? (int)p3.y-(int)p2.y : (int)p2.y-(int)p1.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? (int)p2.y-(int)p1.y : 0))/segment_height;
        vec3 A =               p1 + (p3-p1)*alpha;
        vec3 B = second_half ? p2 + (p3-p2)*beta : p1 + (p2-p1)*beta;
        if (A.x>B.x) std::swap(A, B);
        for (int j=(int)A.x; j<=(int)B.x; j++) {
        	float phi = (int)B.x==(int)A.x ? 1. : (j-(int)A.x)/(float)((int)B.x-(int)A.x);
            vec3 P = A + (B-A)*phi;
            int idx = (int)P.x+(int)P.y*width;
            if(idx>(height*width-1)) continue;
            vec3 v1(p2.x - p1.x, p3.x - p1.x, P.x - p1.x), v2(p2.y - p1.y, p3.y - p1.y, P.y - p1.y);
            vec3 v3 = v1^v2;
            v3.x /= v3.z;
            v3.y /= v3.z;
            vec2 pt = t1*(1 - v3.x - v3.y) + t2*v3.x + t3*v3.y;
            pt.u *= w;
            pt.v *= h;
            int tdx = ((int)pt.v)*w + (int)pt.u;
            if(tdx>(w*h-1)||tdx<0) continue;
            if(zbuffer[idx] < P.z)
			{
				zbuffer[idx] = P.z;
				bitmap[idx] = tex[tdx];
			}
        }
    }
}
