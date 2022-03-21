//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_PERLINMAP_HPP
#define OPENGLPLAYGROUND_PERLINMAP_HPP

#include <map>
#include <memory>
#include "objs/Chunk.hpp"

class PerlinMap {
public:
	PerlinMap(int default_area = 10, int chunk_size = 32);

	void Update(glm::mat4 projection, glm::mat4 view);

private:
	std::map<int, std::map <int,  std::shared_ptr<Chunk>>>	map;
};


#endif //OPENGLPLAYGROUND_PERLINMAP_HPP
