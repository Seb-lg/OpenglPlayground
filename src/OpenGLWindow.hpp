//
// Created by seub on 3/10/22.
//

#ifndef OPENGLPLAYGROUND_OPENGLWINDOW_HPP
#define OPENGLPLAYGROUND_OPENGLWINDOW_HPP


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class OpenGLWindow {
public:
    explicit OpenGLWindow(float fov=90., int width=1920, int height=1080);

    bool update();

public:
    int width;
    int height;
    float fov;
    GLFWwindow *window;
};


#endif //OPENGLPLAYGROUND_OPENGLWINDOW_HPP
