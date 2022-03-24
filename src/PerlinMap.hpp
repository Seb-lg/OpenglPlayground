//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_PERLINMAP_HPP
#define OPENGLPLAYGROUND_PERLINMAP_HPP

#include <map>
#include <memory>
#include "objs/Chunk.hpp"


class PerlinMap {
private:
	struct vec2i {
		vec2i(int x, int y):x(x), y(y){}
		vec2i(float x, float y):x(x), y(y){}
		int x;
		int y;
	};
public:
	PerlinMap(int default_area = 10, int chunk_size = 32);

	void Update(glm::mat4 projection, glm::mat4 view);
	void GenMapAroundPoint(vec2i);

private:
	std::map<int, std::map <int,  std::shared_ptr<Chunk>>>	map;
	int 													_default_area;
	int 													_chunk_size;
	vec2i													_last_position;
};


#endif //OPENGLPLAYGROUND_PERLINMAP_HPP
