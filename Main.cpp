//
// Created by seub on 3/10/22.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include <memory>
#include "src/OpenGLWindow.hpp"
#include "src/Textures.hpp"
#include "src/objs/Renderable.hpp"
#include "helpers/HelperFile.hpp"
#include "helpers/HelperMiscellaneous.hpp"
#include "src/SceneTree.hpp"

int main(){
    std::cout << "Hello OpenGl" << std::endl;
	HelperFile::LoadObj("./assets/untitled.obj");
    OpenGLWindow window;
	auto scene = SceneTree::get();

	srand(time(nullptr));
	std::list<std::shared_ptr<Renderable>> objs;
	for (int i = 0 ; i < 1000; ++i) {
		auto tmp = std::make_shared<Renderable>();
		tmp->vertex_file = "./assets/seb.obj";
		tmp->texture_file = "./assets/tex.png";
		tmp->Init();
		tmp->model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		tmp->model = glm::translate(tmp->model, {((double) rand() / (RAND_MAX))*20 - 10, ((double) rand() / (RAND_MAX))*20 - 10, ((double) rand() / (RAND_MAX))*20 - 10});
		float angle = 20.0f * i;
		tmp->model = glm::rotate(tmp->model, glm::radians(angle), glm::vec3(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX))));
		objs.push_back(tmp);
		scene.root.childs.emplace_back(tmp);
	}

    std::cout << "\nEnd of initialisation..." << std::endl;
	float cam_rot = 0;
    while(window.update()){
		HelperMiscellaneous::PrintFps();
		scene.Update();
		glm::mat4 projection = glm::perspective(glm::radians<float>(window.fov), (float)window.width / (float)window.height, 0.1f, 10000.0f);
		glm::mat4 view = glm::lookAt(window.cameraPos, {0,0,0}, window.cameraUp);

		float dist = 10.;
		window.cameraPos.x = cos(cam_rot)*dist;
		window.cameraPos.z = sin(cam_rot)*dist;
		window.cameraPos.y = cos(cam_rot)*dist;
		cam_rot+=.01;


		for (const auto &obj : objs) {
			obj->DrawInstance(projection, view);
		}
	}
}