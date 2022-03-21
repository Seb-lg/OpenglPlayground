//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_SCENETREE_HPP
#define OPENGLPLAYGROUND_SCENETREE_HPP

#include <list>
#include <memory>
#include "Object.hpp"

struct TreeElem{
	TreeElem(std::shared_ptr<Object> elem=nullptr):elem(elem) {}
	std::shared_ptr<Object> elem;
	std::list<TreeElem> childs;
};

class SceneTree {
public:
	SceneTree() = default;

	static SceneTree &get();

	void Update();
public:
	TreeElem	root;
};


#endif //OPENGLPLAYGROUND_SCENETREE_HPP
