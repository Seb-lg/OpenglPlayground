//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_SCENETREE_HPP
#define OPENGLPLAYGROUND_SCENETREE_HPP

#include <list>
#include <memory>
#include "Object.hpp"

static unsigned int __id__ = 0;

struct TreeElem{
	TreeElem(std::shared_ptr<Object> elem=nullptr):elem(elem) {
		id = __id__;
		++__id__;
	}
	std::shared_ptr<Object> elem;
	unsigned int id;
	std::list<TreeElem> childs;
};

class SceneTree {
private:
	SceneTree(){
		root.elem = std::make_shared<Object>();
	};

	void _recursive_add(TreeElem &add_elem, TreeElem &root, unsigned int parent = 0);
	void _recursive_update(TreeElem &elem);

public:
	static SceneTree &get();

	unsigned int Add(TreeElem child, unsigned int parent=0);
	void Update();
public:
	TreeElem	root;
};


#endif //OPENGLPLAYGROUND_SCENETREE_HPP
