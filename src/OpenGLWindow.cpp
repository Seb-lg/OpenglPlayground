//
// Created by seub on 3/10/22.
//

#include <iostream>
#include <fstream>
#include "OpenGLWindow.hpp"

OpenGLWindow::OpenGLWindow(float fov, int width, int height):fov(fov), width(width), height(height) {
    if (!glfwInit()) {
        std::cout << ("Initialisation failed: glfw\n") << std::endl;
        exit(0);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    this->window = glfwCreateWindow(width, height, "Loup3D", NULL, NULL);
    if (!window) {
        std::cout << ("Failed to create window\n") << std::endl;
        exit(0);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

bool OpenGLWindow::update() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();

//	HelperMiscellaneous::StringToColor("#0B132B"); TODO use the result to drow background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glUseProgram(program);
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}


