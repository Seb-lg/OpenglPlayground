//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_CHUNK_HPP
#define OPENGLPLAYGROUND_CHUNK_HPP


#include "Renderable.hpp"

class Chunk: public Renderable{
public:
	Chunk(glm::vec2 position, int chunk_size);
};


#endif //OPENGLPLAYGROUND_CHUNK_HPP
