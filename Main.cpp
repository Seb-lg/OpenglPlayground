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
	HelperFile::LoadObj("./assets/seb(5).obj");
    OpenGLWindow window;

	Object obj;
//	obj.vertex_file = "./assets/seb.obj";
//	obj.texture_file = "./assets/tex.png";
	obj.vertex_file = "./assets/seb.obj";
	obj.texture_file = "./assets/tex.png";
	obj.Init();
	glm::vec3 cubePositions[] = {
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
    };

    std::cout << "\nEnd of initialisation..." << std::endl;
	float tamer_jb = 0;
    while(window.update()){
		glUseProgram(obj.program);
		glm::mat4 projection = glm::perspective(glm::radians<float>(window.fov), (float)window.width / (float)window.height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(obj.program,"projection"), 1, false, glm::value_ptr(projection));

		// camera/view transformation
//		glm::mat4 view = glm::lookAt(window.cameraPos,  window.cameraPos + window.cameraFront, window.cameraUp);
		glm::mat4 view = glm::lookAt(window.cameraPos, {0,0,0}, window.cameraUp);
		glUniformMatrix4fv(glGetUniformLocation(obj.program,"view"), 1, false, glm::value_ptr(view));

		float dist = 3.;
		window.cameraPos.x = cos(tamer_jb)*dist;
		window.cameraPos.z = sin(tamer_jb)*dist;
		window.cameraPos.y = cos(tamer_jb)*dist;
		tamer_jb+=.01;

		for ( int i = 0 ; i < 1; ++i) {

			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(obj.program,"model"), 1, false, glm::value_ptr(model));

			glBindTexture(GL_TEXTURE_2D, obj.texture);
			glBindVertexArray(obj.vao);
			glDrawArrays(GL_TRIANGLES, 0,obj.obj.size()/5);
		}
    }
}