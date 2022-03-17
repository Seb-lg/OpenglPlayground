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
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);

            db[name] = id;
            std::cout << "Texture loaded:\t" << name << std::endl << "Texture id:\t" << id << std::endl;
        }
        else
        {
            std::cout << "Failed to load texture: " << name << std::endl;
            exit(84);
        }
    }
    return db[name];
}

void Textures::BindTextureToShader(unsigned int program, unsigned int shader, std::string shaderName) {
    glUniform1i(glGetUniformLocation(program, shaderName.c_str()), shader);
}
