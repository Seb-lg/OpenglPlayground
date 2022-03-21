//
// Created by seub on 3/21/22.
//

#include <queue>
#include <glm/gtx/transform.hpp>
#include "SceneTree.hpp"

SceneTree &SceneTree::get() {
	static SceneTree elem;
	return elem;
}


void SceneTree::Update() {
	std::queue<TreeElem> queue;
	for (auto &elem : this->root.childs)
		queue.push(elem);
	while (!queue.empty()) {
		auto tmp = queue.front();
		queue.pop();
		for (auto &child : tmp.childs) {
			child.elem->model =
					tmp.elem->model *
					glm::translate(child.elem->position) *
					child.elem->rotation *
					glm::scale(child.elem->scale) *
					glm::mat4(1.0f);
			for (auto &childs_child : child.childs) {
				queue.push(childs_child);
			}
		}
	}
}
