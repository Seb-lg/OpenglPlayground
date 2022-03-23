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
#include "helpers/HelperInput.hpp"

int main(){
    std::cout << "Hello OpenGl" << std::endl;
	HelperFile::LoadObj("./assets/untitled.obj");
    OpenGLWindow window;
	auto &scene = SceneTree::get();
	PerlinMap map(15, 128);

	auto perso = std::make_shared<Renderable>();
	perso->vertex_file = "./assets/untitled.obj";
	perso->texture_file = "./assets/tex.png";
	perso->LoadVertex();
	perso->Init();

	auto camera = std::make_shared<Object>();
	camera->position.z = 100.;
	auto perso_id = scene.Add({perso, false});
	scene.Add({camera, false}, perso_id);
	scene.Update(true);

	std::cout << "\nEnd of initialisation..." << std::endl;
    while(window.update()){
		HelperMiscellaneous::PrintFps();
		HelperInput::WASDMouvement(window, perso);
		scene.Update();
		glm::mat4 projection = glm::perspective(glm::radians<float>(window.fov), (float)window.width / (float)window.height, 0.1f, 10000.0f);
		glm::mat4 view = glm::lookAt(camera->absolute_position, perso->absolute_position, {0.0f, 1.0f, 0.0f});

		perso->DrawInstance(projection, view);
		map.Update(projection, view);
	}
}