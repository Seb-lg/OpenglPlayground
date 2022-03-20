//
// Created by seub on 3/14/22.
//

#ifndef OPENGLPLAYGROUND_HELPERFILE_HPP
#define OPENGLPLAYGROUND_HELPERFILE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

namespace HelperFile {
    static std::string ReadFile(std::string path) {
        std::ifstream t("./shaders/camera_v.shader");
        return {std::istreambuf_iterator<char>(t),std::istreambuf_iterator<char>()};
    }

	static std::vector<float> LoadObj(std::string path) {
		std::vector<float>	vertices;
		std::vector<float>	texture_pos;
		std::vector<int>	indices;

		std::ifstream in(path, std::ios::in);
		if (!in)
		{
			std::cerr << "Cannot open " << path << std::endl;
			exit(1);
		}

		std::string line;
		int vert_info = -1;
		int line_nb = 0;
		while (getline(in, line))
		{
			line_nb++;
			if (line.substr(0,2) == "v ")
			{
				std::istringstream s(line.substr(2));
				float x, y, z;
				s >> x; s >> y; s >> z;
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
			else if (line.substr(0,2) == "f ")
			{
				line = line.substr(2);
				if (vert_info == -1) {
					vert_info = std::count(line.begin(), line.end(), '/') / 3 + 1;
				}

				int nb_vertice = std::count(line.begin(), line.end(), ' ') + 1;
				if (nb_vertice != 3) {
					std::cout << nb_vertice << std::endl;
					std::cout << "Not handled !\n" << line_nb << ":\t" << path << std::endl;
					exit(0);
				}

				std::replace(line.begin(), line.end(), '/', ' ');
				std::istringstream s(line);
				int a,b,c,d,e,f,g,h,i = -1;
				s >> a;s >> b;s >> c;s >> d;s >> e;s >> f;s >> g;s >> h;s >> i;
				--a;--b;--c;--d;--e;--f;--g;--h;--i;
				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(c);
				indices.push_back(d);
				indices.push_back(e);
				indices.push_back(f);
				if (vert_info == 3){
					indices.push_back(g);
					indices.push_back(h);
					indices.push_back(i);
				}

			}
			else if (line.substr(0,3) == "vt ")
			{
				std::istringstream s(line.substr(3));
				float x, y;
				s >> x; s >> y;
				texture_pos.push_back(x);
				texture_pos.push_back(y);
			}
			/* anything else is ignored */
		}

//		normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
//		for (int i = 0; i < elements.size(); i+=3)
//		{
//			GLushort ia = elements[i];
//			GLushort ib = elements[i+1];
//			GLushort ic = elements[i+2];
//			glm::vec3 normal = glm::normalize(glm::cross(
//					glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
//					glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
//			normals[ia] = normals[ib] = normals[ic] = normal;
//		}

		std::vector<float> obj;
		for (int i = 0; i < indices.size(); i+=vert_info) {
			// position
			obj.push_back(vertices[indices[i + 0]*3 + 0]);
			obj.push_back(vertices[indices[i + 0]*3 + 1]);
			obj.push_back(vertices[indices[i + 0]*3 + 2]);

			// texture
			obj.push_back(texture_pos[indices[i + 1]*2 + 0]);
			obj.push_back(texture_pos[indices[i + 1]*2 + 1]);

			// normal -> unset
		}

		return obj;
	}
}

#endif //OPENGLPLAYGROUND_HELPERFILE_HPP
