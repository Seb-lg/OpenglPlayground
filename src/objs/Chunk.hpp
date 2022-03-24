//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_CHUNK_HPP
#define OPENGLPLAYGROUND_CHUNK_HPP


#include <thread>
#include <mutex>
#include "Renderable.hpp"
#include "../../helpers/YOLO.hpp"

class Chunk: public Renderable{
public:
	Chunk(glm::vec2 position, int chunk_size, float threshold = 175.f);

	void Load();
	void Unload();
	void DrawInstance(glm::mat4 projection, glm::mat4 view);

private:
	void gen_map(glm::vec2 position, int chunk_size);

	void gen_square(int x, int y, int chunk_size, YOLO::Image &image);
	bool gen_triangle(glm::vec2 a,glm::vec2 b,glm::vec2 c, int chunk_size, YOLO::Image &image);

public:
	bool to_delete;
	std::mutex obj_generation;
	bool 		loaded;
private:
	YOLO::Image	image;
	float		threshold;
	std::thread threaded_gen;
};


#endif //OPENGLPLAYGROUND_CHUNK_HPP
