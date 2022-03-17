//
// Created by seub on 3/10/22.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "src/OpenGLWindow.hpp"
#include "src/Textures.hpp"
#include "src/Object.hpp"
#include "test/Shapes.hpp"
#include "helpers/HelperFile.hpp"

int main(){
    std::cout << "Hello OpenGl" << std::endl;
	HelperFile::LoadObj("./assets/cube.obj");
    OpenGLWindow window;

    //  Load Textures
    //  TODO add fragment shader and check if Textures class correctly load textures
//    Textures textures;
//    textures["./assets/awesomeface.bmp"];
//    textures["./assets/container.bmp"];
//    textures.BindTextureToShader(window.program, 0,"texture1");
//    textures.BindTextureToShader(window.program, 1,"texture2");

	Object obj;
	obj.vertex_file = "./assets/cube.obj";
//	obj.vertex_file = "./assets/bugatti.obj";
//	obj.vertex_shader = "./shaders/camera_v.shader";
//	obj.fragment_shader = "./shaders/camera_f.shader";
	obj.Init();

	/*std::vector<Cube> test(10);
//	Cube cube;

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    */glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };/*
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/

    std::cout << "\nEnd of initialisation..." << std::endl;
    while(window.update()){
		glUseProgram(obj.program);
		glm::mat4 projection = glm::perspective(glm::radians<float>(window.fov), (float)window.width / (float)window.height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(obj.program,"projection"), 1, false, glm::value_ptr(projection));

		// camera/view transformation
		glm::mat4 view = glm::lookAt(window.cameraPos, window.cameraPos + window.cameraFront, window.cameraUp);
		glUniformMatrix4fv(glGetUniformLocation(obj.program,"view"), 1, false, glm::value_ptr(view));

		for ( int i = 0 ; i < 10; ++i) {

			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(obj.program,"model"), 1, false, glm::value_ptr(model));

			glBindTexture(GL_TEXTURE_2D, obj.texture);
			glBindVertexArray(obj.vao);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0,obj.obj.size()/6);
		}
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, textures["./assets/awesomeface.bmp"]);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, textures["./assets/container.bmp"]);
//
//        glm::mat4 projection = glm::perspective(glm::radians<float>(window.fov), (float)window.width / (float)window.height, 0.1f, 100.0f);
//        glUniformMatrix4fv(glGetUniformLocation(window.program,"projection"), 1, false, glm::value_ptr(projection));
//
//        // camera/view transformation
//        glm::mat4 view = glm::lookAt(window.cameraPos, window.cameraPos + window.cameraFront, window.cameraUp);
//        glUniformMatrix4fv(glGetUniformLocation(window.program,"view"), 1, false, glm::value_ptr(view));
//
//        // render boxes
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            glUniformMatrix4fv(glGetUniformLocation(window.program,"model"), 1, false, glm::value_ptr(model));
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
    }
}