//
// Created by seub on 3/10/22.
//

#include <iostream>
#include <GL/glew.h>
#include <cstring>
#include "Textures.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../helpers/stb_image.hpp"

unsigned int Textures::operator[](std::string name) {
    if (!db.contains(name)) {
        unsigned int id;
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);

            db[name] = id;
            std::cout << "Texture loaded:\t" << name << std::endl << "Texture id:\t" << id << std::endl;
        }
        else
        {
            std::cout << "Failed to load texture: " << name << std::endl;
        }
    }
    return db[name];
}

Textures::Image Textures::LoadBMP(std::string path) {
    std::cout << "Reading image " << path << std::endl;
    int width = -1;
    int height = -1;
    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    // Actual RGB data
    std::vector<unsigned char> data;

    // Open the file
    FILE *file = fopen(path.c_str(), "rb");
    if (!file) {
        printf("Image could not be opened\n");
        return {};
    }

    // Read the header, i.e. the 54 first bytes

    // If less than 54 byes are read, problem
    if (fread(header, 1, 54, file) != 54) {
        printf("Not a correct BMP file\n");
        return {};
    }
    // A BMP files always begins with "BM"
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return {};
    }
    // Make sure this is a 24bpp file
    if (*(int *)&(header[0x1E]) != 0) {
        printf("Not a correct BMP file\n");
        return {};
    }
    if (*(int *)&(header[0x1C]) != 24) {
        printf("Not a correct BMP file\n");
        return {};
    }

    // Read the information about the image
    dataPos = *(int *)&(header[0x0A]);
    imageSize = *(int *)&(header[0x22]);
    width = *(int *)&(header[0x12]);
    height = *(int *)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = width * height *
                    3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)
        dataPos = 54; // The BMP header is done that way

    // Create a buffer
    data.resize(imageSize);

    // Read the actual data from the file into the buffer
    fread(data.data(), 1, imageSize, file);

    // Everything is in memory now, the file wan be closed
    fclose(file);

    // swap y-axis
    unsigned char *tmpBuffer = (unsigned char *)malloc(width * 3);
    int size = width * 3;
    for (int i = 0; i < height / 2; i++) {
        // copy row i to tmp
        memcpy(tmpBuffer, data.data() + width * 3 * i, size);
        // copy row h-i-1 to i
        memcpy(data.data() + width * 3 * i, data.data() + width * 3 * (height - i - 1),
               size);
        // copy tmp to row h-i-1
        memcpy(data.data() + width * 3 * (height - i - 1), tmpBuffer, size);
    }
    free(tmpBuffer);

    unsigned char tmp;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < height; x++) {
            tmp = data[y * width * 3 + (x * 3)];
            data[y * width * 3 + (x * 3)] = data[y * width * 3 + (x * 3) + 2];
            data[y * width * 3 + (x * 3) + 2] = tmp;
        }

    return {width, height, data};
}
