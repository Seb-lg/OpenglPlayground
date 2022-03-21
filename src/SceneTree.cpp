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


void SceneTree::_recursive_add(TreeElem &add_elem, TreeElem &root, unsigned int parent) {
	if (root.id == parent)
		root.childs.push_back(add_elem);
	for (auto &child : root.childs)
		_recursive_add(add_elem, child, parent);
}

unsigned int SceneTree::Add(TreeElem child, unsigned int parent) {
	if (child.id == 0)
		this->root = child;
	else
		_recursive_add(child, this->root, parent);
	return child.id;
}

void SceneTree::_recursive_update(TreeElem &elem) {
	for (auto &child : elem.childs) {
		child.elem->model =
				elem.elem->model *
				glm::translate(child.elem->position) *
				child.elem->rotation *
				glm::scale(child.elem->scale) *
				glm::mat4(1.0f);
		child.elem->absolute_position = child.elem->model[3];
		_recursive_update(child);
	}
}

void SceneTree::Update() {
	_recursive_update(this->root);
}
