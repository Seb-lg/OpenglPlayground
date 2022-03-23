//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_CHUNK_HPP
#define OPENGLPLAYGROUND_CHUNK_HPP


#include "Renderable.hpp"
#include "../../helpers/YOLO.hpp"

class Chunk: public Renderable{
public:
	Chunk(glm::vec2 position, int chunk_size, float threshold = 175.f);

	void Load();
	void Unload();

private:
	void gen_square(int x, int y, int chunk_size, YOLO::Image &image);
	bool gen_triangle(glm::vec2 a,glm::vec2 b,glm::vec2 c, int chunk_size, YOLO::Image &image);

private:
	YOLO::Image	image;
	float		threshold;
};


#endif //OPENGLPLAYGROUND_CHUNK_HPP
