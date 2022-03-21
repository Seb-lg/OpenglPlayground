//
// Created by seub on 3/21/22.
//

#include "YOLO.hpp"
#include "HelperFile.hpp"
#include "stb_image.hpp"

YOLO &YOLO::get() {
	static YOLO yolo;
	return yolo;
}

std::vector<float> YOLO::GetObj(std::string path) {
	auto &yolo = YOLO::get();

	if (!yolo._objs.contains(path))
		yolo._objs.emplace(path, HelperFile::LoadObj(path));

	return yolo._objs[path];
}

YOLO::Image YOLO::GetImage(std::string path) {
	auto &yolo = YOLO::get();

	if (!yolo._imgs.contains(path)) {
		Image image;
		stbi_set_flip_vertically_on_load(true);
		image.data = stbi_load(path.data(), &image.width, &image.height, &image.nrChannels, 0);
		yolo._imgs.emplace(path, image);
	}

	return yolo._imgs[path];
}
