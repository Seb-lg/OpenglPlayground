//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_OBJECT_HPP
#define OPENGLPLAYGROUND_OBJECT_HPP


#include <glm/detail/type_mat4x4.hpp>

class Object {
public:
	Object();

	void UpdateModel();

public:
	glm::mat4	model;
	glm::vec3	position;
	glm::mat4	rotation;
	glm::vec3	scale;
	glm::vec3	absolute_position;
};


#endif //OPENGLPLAYGROUND_OBJECT_HPP
