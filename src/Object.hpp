//
// Created by seub on 3/10/22.
//

#ifndef OPENGLPLAYGROUND_OBJECT_HPP
#define OPENGLPLAYGROUND_OBJECT_HPP


#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/detail/type_mat4x4.hpp>


class Object {
public:
	Object() = default;

	void Init();
	void Draw();

private:
	void LoadVertex();
	void InitShaders();


public:
	std::string vertex_file;
	std::string texture_file;

	GLint	program;
	GLuint	vao;
	GLuint	vbo;
	GLuint	texture;

	std::vector<glm::vec3>	vertices;
	std::vector<glm::vec2>	uvs;
	std::vector<glm::vec3>	normals;
	std::vector<float>		obj;
};

#endif //OPENGLPLAYGROUND_OBJECT_HPP