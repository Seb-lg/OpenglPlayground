//
// Created by seub on 3/21/22.
//

#include <iostream>
#include "PerlinMap.hpp"
#include "SceneTree.hpp"

PerlinMap::PerlinMap(int default_area, int chunk_size) {
	auto &scene = SceneTree::get();
	for (int y = 0; y < default_area; ++y)
	for (int x = 0; x < default_area; ++x) {
		/*map[x].emplace(std::piecewise_construct,
					   std::forward_as_tuple(y),
					   std::forward_as_tuple(glm::vec2({x * chunk_size, y * chunk_size}), chunk_size));*/
		map[x].emplace(y, std::make_shared<Chunk>(glm::vec2({x * chunk_size, y * chunk_size}), chunk_size));
		scene.Add({map[x][y]});
		std::cout << "[";
		float progress = (float)(x + y*default_area)/(float)(default_area*default_area);
		int pos = 100 * progress;
		for (int i = 0; i < 100; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		std::cout << "] " << int(progress * 100.0) << " %\r";
		std::cout.flush();
	}
}

void PerlinMap::Update(glm::mat4 projection, glm::mat4 view) {
	for (auto &x_elem : map)
	for (auto &y_elem : x_elem.second)
		y_elem.second->DrawInstance(projection, view);
}
