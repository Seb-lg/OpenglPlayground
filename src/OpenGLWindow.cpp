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

    program = glCreateProgram();

    //  Compile camera's vertex shader
    unsigned int sVertex = glCreateShader(GL_VERTEX_SHADER);
    std::ifstream t("./shaders/camera.shader");
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
    }
    glAttachShader(program, sVertex);

    // Compile program linked shaders
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "Error during the compilation of the program shaders" << std::endl
                  << infoLog << std::endl;
    }
    glDeleteShader(sVertex);
}

bool OpenGLWindow::update() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}


