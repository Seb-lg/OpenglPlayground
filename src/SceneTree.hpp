//
// Created by seub on 3/21/22.
//

#ifndef OPENGLPLAYGROUND_SCENETREE_HPP
#define OPENGLPLAYGROUND_SCENETREE_HPP

#include <list>
#include <memory>
#include "Object.hpp"

static unsigned int GetUniqueId(){
	static unsigned int _id = 0;
	++_id;
	return  _id -1;
}

struct TreeElem{
	TreeElem(std::shared_ptr<Object> elem=nullptr, bool _static = false):elem(elem), _static(_static) {
		id = GetUniqueId();
	}
	std::shared_ptr<Object> elem;
	unsigned int id;
	std::list<TreeElem> childs;
	bool _static;
};

class SceneTree {
private:
	SceneTree(){
		root.elem = std::make_shared<Object>();
	};

	void _recursive_add(TreeElem &add_elem, TreeElem &root, unsigned int parent = 0);
	void _recursive_get(TreeElem &elem, unsigned int id, TreeElem **ret);
	void _recursive_update(TreeElem &elem, bool force);

public:
	static SceneTree &get();

	unsigned int Add(TreeElem child, unsigned int parent=0);
	TreeElem &Get(unsigned int id);
	void Update(bool force = false);
public:
	TreeElem	root;
};


#endif //OPENGLPLAYGROUND_SCENETREE_HPP
