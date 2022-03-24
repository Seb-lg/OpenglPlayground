//
// Created by seub on 3/21/22.
//

#include <iostream>
#include <thread>
#include "Chunk.hpp"
#include "../../helpers/PerlinNoise.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../helpers/stb_image_writer.hpp"


Chunk::Chunk(glm::vec2 position, int chunk_size, float threshold):threshold(threshold),loaded(false) {
	obj_generation.lock();
	this->position.x = position.x;
	this->position.y = position.y;

	if (false) {// file exist
	} else {
//		threaded_gen = std::thread([this,position,chunk_size,threshold](){this->gen_map(position,chunk_size,threshold);});
		std::thread tmp(&Chunk::gen_map, std::ref(*this),position, chunk_size );
		tmp.detach();
		threaded_gen.swap(tmp);
//		gen_map(position,chunk_size);
	}
}

void Chunk::Load() {
	this->texture_file = "./assets/chunks/" + std::to_string(position.x) + '_' + std::to_string(position.y) + ".handmade";
	YOLO::SetImage(this->texture_file, image);
	this->Init();

//	stbi_write_png(this->texture_file.data(), image.width, image.height, image.nrChannels, image.data,
//				   image.width * image.nrChannels);
}

void Chunk::Unload() {

}

void Chunk::gen_map(glm::vec2 position, int chunk_size) {
	static const siv::PerlinNoise::seed_type seed = 19837u;
	static const siv::PerlinNoise perlin{seed};
	int img_size = chunk_size;

	loaded = false;
	image.height = image.width = img_size;
	image.nrChannels = 4;
	image.data = new unsigned char[(img_size+1) * (img_size+1) * image.nrChannels];
	float power = (float)chunk_size/(float)img_size;
	power = power*0.001;
	auto datap = image.data;
	for (int y = 0; y <= img_size; ++y) {
		for (int x = 0; x <= img_size; ++x) {
			unsigned char val = 255.f * perlin.octave2D_01(((((position.x/(chunk_size + 1)) * img_size) + (float)(x)) * power),
														   ((((position.y/(chunk_size + 1)) * img_size) + (float)(y)) * power),
														   1);
			datap[0] = val;
			datap[1] = val;
			datap[2] = val;
			if (image.nrChannels == 4)
				datap[3] = val;
			datap += image.nrChannels;
		}
	}
	for (int y = 0; y < img_size; ++y) {
		for (int x = 0; x < img_size; ++x) {
			gen_square(x, y, chunk_size+1, image);
		}
	}
	unsigned char *src, *dest;
	src = image.data;
	dest = image.data;
	for (int y = 0; y < img_size; ++y) {
		memcpy(dest , src , img_size * image.nrChannels);
		dest += img_size*image.nrChannels;
		src += (img_size+1)*image.nrChannels;
	}
	obj_generation.unlock();
}

void Chunk::gen_square(int x, int y, int chunk_size, YOLO::Image &image) {
	bool type = false;
	type = gen_triangle({x,y},{x+1,y},{x,y+1}, chunk_size, image);
	type = gen_triangle({x+1,y+1},{x+1,y},{x,y+1}, chunk_size, image) || type;
	if (type)return;
	gen_triangle({x,y},{x+1,y},{x+1,y+1}, chunk_size, image);
	gen_triangle({x,y},{x,y+1},{x+1,y+1}, chunk_size, image);
}

bool Chunk::gen_triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, int chunk_size, YOLO::Image &image) {
	auto map = image.data;
	int line = chunk_size * image.nrChannels;
	if (map[(int)(a.x*image.nrChannels + a.y*line)] > threshold && map[int((b.x)*image.nrChannels + b.y*line)] > threshold && map[int(c.x*image.nrChannels + (c.y)*line)] > threshold) {
		std::vector<float> tmp;
		tmp = {
				(float)(a.x), (float)(a.y), 0.0f, (float)(a.x)/chunk_size, (float)(a.y)/chunk_size,
				(float)(b.x), (float)(b.y), 0.0f, (float)(b.x)/chunk_size, (float)(b.y)/chunk_size,
				(float)(c.x), (float)(c.y), 0.0f, (float)(c.x)/chunk_size, (float)(c.y)/chunk_size
		};
		this->obj.insert(this->obj.end(), tmp.begin(), tmp.end());
		return true;
	}
	return false;
}

void Chunk::DrawInstance(glm::mat4 projection, glm::mat4 view) {
	if (loaded)
		Renderable::DrawInstance(projection, view);
	else
		if (obj_generation.try_lock()) {
			obj_generation.unlock();
			if (!loaded) {
				UpdateModel();
				Load();
				loaded = true;
			}
			Renderable::DrawInstance(projection, view);
		}
}
