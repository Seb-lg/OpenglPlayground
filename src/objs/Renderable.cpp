//
// Created by seub on 3/14/22.
//

#include <iterator>
#include <cstring>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Renderable.hpp"
#include "../../helpers/stb_image.hpp"
#include "../../helpers/HelperFile.hpp"
#include "../../helpers/YOLO.hpp"


void Renderable::Init() {
	LoadVertex();
	program = glCreateProgram();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, obj.size()*sizeof(float), obj.data(), GL_STATIC_DRAW);

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(0*sizeof(float)));
	// texture coord attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(float)));
	// normals
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(5*sizeof(float)));

	//	LOAD TEXTURE
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	YOLO::Image image = YOLO::GetImage(texture_file);

//	int width, height, nrChannels;
//	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load(texture_file.data(), &width, &height, &nrChannels, 0);
	if (image.data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, image.nrChannels == 4 ? GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, image.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
//	stbi_image_free(image.data);

	InitShaders();
}

void Renderable::InitShaders() {
	//  Compile camera's vertex shader
	unsigned int sVertex = glCreateShader(GL_VERTEX_SHADER);
	std::ifstream t("./shaders/camera_v.shader");
	auto tmp = std::string((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	const char *file = tmp.c_str();
	glShaderSource(sVertex, 1, &file, NULL);
	glCompileShader(sVertex);

	//  Check compilation
	int success;
	glGetShaderiv(sVertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(sVertex, 1024, NULL, infoLog);
		std::cout << "Error during the compilation of the camera's vertex shader"
				  << infoLog << std::endl;
		exit(84);
	}

	glAttachShader(program, sVertex);
	//  Compile obj fragment shader
	unsigned int sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	t = std::ifstream("./shaders/camera_f.shader");
	tmp = std::string((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	file = tmp.c_str();
	glShaderSource(sFragment, 1, &file, NULL);
	glCompileShader(sFragment);

	//  Check compilation
	glGetShaderiv(sFragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(sFragment, 1024, NULL, infoLog);
		std::cout << "Error during the compilation of the object's fragment shader"
				  << infoLog << std::endl;
		exit(84);
	}
	glAttachShader(program, sFragment);

	// Compile program linked shaders
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		std::cout << "Error during the compilation of the program shaders" << std::endl
				  << infoLog << std::endl;
		exit(84);
	}
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

void Renderable::LoadVertex() {
	obj = YOLO::GetObj(vertex_file);
}

void Renderable::DrawInstance(glm::mat4 projection, glm::mat4 view) {
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program,"projection"), 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(program,"view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program,"model"), 1, false, glm::value_ptr(model));

	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0,obj.size()/5);
}