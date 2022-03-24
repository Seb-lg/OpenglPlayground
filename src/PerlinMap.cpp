//
// Created by seub on 3/21/22.
//

#include <iostream>
#include <thread>
#include "PerlinMap.hpp"
#include "SceneTree.hpp"
#include "../helpers/HelperMiscellaneous.hpp"

PerlinMap::PerlinMap(int default_area, int chunk_size):_default_area(default_area), _chunk_size(chunk_size), _last_position(42,42) {
	GenMapAroundPoint({0,0});
}

void PerlinMap::Update(glm::mat4 projection, glm::mat4 view) {
	for (auto &x_elem : map)
	for (auto &y_elem : x_elem.second)
		if (y_elem.second)
			y_elem.second->DrawInstance(projection, view);
}

void PerlinMap::GenMapAroundPoint(vec2i position) {
	if ((int)(position.x) / _chunk_size == _last_position.x && (int)(position.y) / _chunk_size == _last_position.y){
		return;
	} else {
		_last_position.x = (int)(position.x) / _chunk_size;
		_last_position.y = (int)(position.y) / _chunk_size;
	}
	auto &scene = SceneTree::get();

	for (auto &xs: map)
		for (auto &ys: xs.second)
			if (ys.second)
				ys.second->to_delete = true;

	for (int y = -_default_area; y <= _default_area; ++y) {
		for (int x = -_default_area; x <= _default_area; ++x) {
			auto &item = map[_last_position.x + x][_last_position.y + y];
			if (item) {
				item->to_delete = false;
			} else {
				item = std::make_shared<Chunk>(
						glm::vec2(
								(_last_position.x + x) * _chunk_size,
								(_last_position.y + y) * _chunk_size),
								_chunk_size,
								140);
			}
		}
	}

	std::list<vec2i> to_delete;
	for (auto &xs: map)
		for (auto &ys: xs.second)
			if (ys.second && ys.second->to_delete && ys.second->loaded)
				to_delete.emplace_back(xs.first, ys.first);
	for (auto &elem : to_delete)
		map[elem.x].erase(elem.y);
}
