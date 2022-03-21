//
// Created by seub on 3/21/22.
//

#include "Object.hpp"

#define DEFAULT_MODEL		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}
#define DEFAULT_POSITION	{0.f, 0.f, 0.f}
#define DEFAULT_ROTATION	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}
#define DEFAULT_SCALE		{1.f, 1.f, 1.f}

Object::Object():
		model(DEFAULT_MODEL), position(DEFAULT_POSITION), rotation(DEFAULT_ROTATION), scale(DEFAULT_SCALE){

}
