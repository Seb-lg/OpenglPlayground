//
// Created by seub on 3/22/22.
//

#ifndef OPENGLPLAYGROUND_HELPERINPUT_HPP
#define OPENGLPLAYGROUND_HELPERINPUT_HPP

#include "../src/OpenGLWindow.hpp"
#include "../src/SceneTree.hpp"

namespace HelperInput {
	static void WASDMouvement(OpenGLWindow &window, std::shared_ptr<Object> elem) {
		float deltatime = 0.8f;
		float speed = 5.f;
		if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS) {
			elem->position.y += speed * deltatime;
		}
		if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS) {
			elem->position.y -= speed * deltatime;
		}
		if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS) {
			elem->position.x -= speed * deltatime;
		}
		if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS) {
			elem->position.x += speed * deltatime;
		}
		if (glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			elem->position.z += speed * deltatime;
		}
		if (glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			elem->position.z -= speed * deltatime;
		}
	}
}

#endif //OPENGLPLAYGROUND_HELPERINPUT_HPP
