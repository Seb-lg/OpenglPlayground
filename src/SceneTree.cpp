//
// Created by seub on 3/21/22.
//

#include <queue>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "SceneTree.hpp"

SceneTree &SceneTree::get() {
	static SceneTree elem;

	return elem;
}


void SceneTree::_recursive_add(TreeElem &add_elem, TreeElem &root, unsigned int parent) {
	if (root.id == parent) {
		add_elem.elem->model =
				root.elem->model *
				glm::translate(add_elem.elem->position) *
				add_elem.elem->rotation *
				glm::scale(add_elem.elem->scale) *
				glm::mat4(1.0f);
		add_elem.elem->absolute_position = add_elem.elem->model[3];
		root.childs.push_back(add_elem);
		return;
	}
	for (auto &child : root.childs)
		_recursive_add(add_elem, child, parent);
}

unsigned int SceneTree::Add(TreeElem child, unsigned int parent) {
	if (child.id == 0) {
		this->root = child;
	}
	else
		_recursive_add(child, this->root, parent);
	return child.id;
}

void SceneTree::_recursive_get(TreeElem &elem, unsigned int id, TreeElem **ret) {
	if (elem.id == id)
		*ret = &elem;
	for (auto &child : elem.childs) {
		_recursive_get(child, id, ret);
	}
}

TreeElem &SceneTree::Get(unsigned int id) {
	TreeElem *ret;
	_recursive_get(root, id, &ret);
	return *ret;
}

void SceneTree::_recursive_update(TreeElem &elem, bool force) {
	for (auto &child : elem.childs) {
		if (child._static && !force)
			continue;

		child.elem->model =
				elem.elem->model *
				glm::translate(child.elem->position) *
				child.elem->rotation *
				glm::scale(child.elem->scale) *
				glm::mat4(1.0f);
		child.elem->absolute_position = child.elem->model[3];
		_recursive_update(child, force);
	}
}

void SceneTree::Update(bool force) {
	_recursive_update(this->root, false);
}
