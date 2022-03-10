//
// Created by seub on 3/10/22.
//

#ifndef OPENGLPLAYGROUND_TEXTURES_HPP
#define OPENGLPLAYGROUND_TEXTURES_HPP


#include <map>
#include <string>
#include <vector>

class Textures {
private:
    struct Image{
        int width;
        int height;
        std::vector<unsigned char> data;
    };
public:
    Textures() = default;

    unsigned int operator[](std::string path);

private:
    Image LoadBMP(std::string path);

public:
    std::map<std::string, unsigned int> db;
};


#endif //OPENGLPLAYGROUND_TEXTURES_HPP
