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

//    program = glCreateProgram();


//    this->InitShaders();

    //  Init camera position and orientation
    this->cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
}

void OpenGLWindow::InitShaders() {
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


