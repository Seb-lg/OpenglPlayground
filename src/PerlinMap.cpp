//
// Created by seub on 3/21/22.
//

#include <iostream>
#include <thread>
#include "PerlinMap.hpp"
#include "SceneTree.hpp"
#include "../helpers/HelperMiscellaneous.hpp"

PerlinMap::PerlinMap(int default_area, int chunk_size) {
	auto &scene = SceneTree::get();
	int nb = 0;
	for (int y = 0; y < default_area; ++y) {
		for (int x = 0; x < default_area; ++x) {
			// Todo: find a way to multi-thread this part
			auto tmp = std::make_shared<Chunk>(glm::vec2({(x-(default_area/2)) * chunk_size, (y-(default_area/2)) * chunk_size}), chunk_size);
			map[x][y] = tmp;
			scene.Add({tmp, true});

			float progress = (float)(nb)/(float)(default_area*default_area);
			HelperMiscellaneous::PrintProgress(progress);
			++nb;
		}
	}
}

void PerlinMap::Update(glm::mat4 projection, glm::mat4 view) {
	for (auto &x_elem : map)
	for (auto &y_elem : x_elem.second)
		y_elem.second->DrawInstance(projection, view);
}
