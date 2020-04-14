#include "resources.h"
#include <fstream>
#include <sstream>

Model::Model(const char* model_name, const char* tex_name)
{
	std::ifstream file(model_name);
	if(!file.is_open()) return;
	std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            vec3 v;
            iss >> v.x >> v.y >> v.z;
            verts.push_back(v);
        } else if (!line.compare(0, 2, "vt")) {
            iss >> trash >> trash;
            vec2 v;
            iss >> v.u >> v.v;
            tverts.push_back(v);
        }else if (!line.compare(0, 2, "f ")) {
            int itrash, idx, itx;
            iss >> trash;
            while (iss >> idx >> trash >> itx >> trash >> itrash) {
                idx--;
                --itx;
                faces.push_back(idx);
                tfaces.push_back(itx);
            }
        }
    }
    file.close();
    file.open(tex_name);
	if(!file.is_open()) return;
	BITMAPFILEHEADER filehead;
	file.read((char*)&filehead, sizeof(BITMAPFILEHEADER));
	infohead = (BITMAPINFOHEADER*) (new BYTE[filehead.bfOffBits - sizeof(BITMAPFILEHEADER)]);
	file.read((char*)infohead, filehead.bfOffBits - sizeof(BITMAPFILEHEADER));
	w = infohead->biWidth;
	h = infohead->biHeight<0 ? -infohead->biHeight : infohead->biHeight;
	tex = new RGBTRIPLE[w*h];
	file.read((char*)tex, w*h*3);
	file.close();
}
