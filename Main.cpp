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
#include "src/PerlinMap.hpp"

int main(){
    std::cout << "Hello OpenGl" << std::endl;
	HelperFile::LoadObj("./assets/untitled.obj");
    OpenGLWindow window;
	auto &scene = SceneTree::get();
	PerlinMap map(10, 1);

	srand(time(nullptr));
	std::list<std::shared_ptr<Renderable>> objs;
	for (int i = 0 ; i < 1; ++i) {
		auto tmp = std::make_shared<Renderable>();
		tmp->vertex_file = "./assets/untitled.obj";
		tmp->texture_file = "./assets/tex.png";
		tmp->Init();
		tmp->model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		tmp->model = glm::translate(tmp->model, {((double) rand() / (RAND_MAX))*20 - 10, ((double) rand() / (RAND_MAX))*20 - 10, ((double) rand() / (RAND_MAX))*20 - 10});
		float angle = 20.0f * i;
		tmp->model = glm::rotate(tmp->model, glm::radians(angle), glm::vec3(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX))));
		objs.push_back(tmp);
		scene.Add({tmp});
	}
	auto perso = std::make_shared<Renderable>();
	perso->vertex_file = "./assets/seb.obj";
	perso->texture_file = "./assets/tex.png";
	perso->LoadVertex();
	perso->Init();

	auto camera = std::make_shared<Object>();
	camera->position = window.cameraPos;
	camera->position.z = 10.;
//	exit(0);
	auto perso_id = scene.Add({perso});
	scene.Add({camera}, perso_id);

    std::cout << "\nEnd of initialisation..." << std::endl;
	float cam_rot = 0;
    while(window.update()){
		HelperMiscellaneous::PrintFps();
		scene.Update();
		glm::mat4 projection = glm::perspective(glm::radians<float>(window.fov), (float)window.width / (float)window.height, 0.1f, 10000.0f);
		glm::mat4 view = glm::lookAt(camera->absolute_position, perso->absolute_position, window.cameraUp);

		float dist = 10.;
//		perso->position.x = cos(cam_rot)*dist;
//		perso->position.z = sin(cam_rot)*dist;
//		perso->position.y = cos(cam_rot)*dist;
		cam_rot+=.01;

		perso->DrawInstance(projection, view);
		map.Update(projection, view);
//		for (const auto &obj : objs) {
//			obj->DrawInstance(projection, view);
//		}
	}
}