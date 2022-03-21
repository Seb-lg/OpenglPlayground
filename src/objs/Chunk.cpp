//
// Created by seub on 3/21/22.
//

#include <iostream>
#include "Chunk.hpp"
#include "../../helpers/YOLO.hpp"
#include "../../helpers/PerlinNoise.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../../helpers/stb_image_writer.hpp"

Chunk::Chunk(glm::vec2 position, int chunk_size) {
	this->position.x = position.x;
	this->position.y = position.y;
	float half_size = ((float)(chunk_size))/2.f;
	this->obj = {
			half_size, half_size, 0.0f, 1.0f, 1.0f,
			half_size, -half_size, 0.0f, 1.0f, 0.0f,
			-half_size, -half_size, 0.0f, 0.0f, 0.0f,
			half_size, half_size, 0.0f, 1.0f, 1.0f,
			-half_size, -half_size, 0.0f, 0.0f, 0.0f,
			-half_size, half_size, 0.0f, 0.0f, 1.0f
	};

	static const siv::PerlinNoise::seed_type seed = 19837u;
	static const siv::PerlinNoise perlin{seed};
	int img_size = 512;
	YOLO::Image image;
	image.height = image.width = img_size;
	image.nrChannels = 3;
	image.data = new unsigned char[img_size * img_size * image.nrChannels];
	float power = (float)chunk_size/(float)img_size;
	power = power*0.01;
	auto datap = image.data;
	for (int y = 0; y < img_size; ++y) {
		for (int x = 0; x < img_size; ++x) {
			unsigned char val = 255.f * perlin.octave2D_01(((((position.x/chunk_size) * img_size) + (float)(x)) * power), ((((position.y/chunk_size) * img_size) + (float)(y)) * power), 4);
			datap[0] = val;
			datap[1] = val;
			datap[2] = val;
			datap += image.nrChannels;
		}

	}

	this->texture_file = "./assets/chunks/" + std::to_string(position.x) + '_' + std::to_string(position.y) + ".handmade";
	YOLO::SetImage(this->texture_file, image);
	this->Init();
//	stbi_write_png(this->texture_file.data(), image.width, image.height, image.nrChannels, image.data,
//				   image.width * image.nrChannels);
}
