//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_YOLO_HPP
#define OPENGLPLAYGROUND_YOLO_HPP

#include <vector>
#include <string>
#include <map>
#include <iostream>

/// You Only Load Once

class YOLO {
public:
	struct Image {
		int width;
		int height;
		int nrChannels;

		unsigned char *data;
	};
private:
	static YOLO &get();
public:
	static std::vector<float> GetObj(std::string path);
	static Image GetImage(std::string path);

private:
	std::map<std::string, std::vector<float>>	_objs;
	std::map<std::string, Image>				_imgs;
};


#endif //OPENGLPLAYGROUND_YOLO_HPP
