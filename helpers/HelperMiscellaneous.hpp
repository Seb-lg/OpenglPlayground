//
// Created by seub on 3/20/22.
//

#ifndef OPENGLPLAYGROUND_HELPERMISCELLANEOUS_HPP
#define OPENGLPLAYGROUND_HELPERMISCELLANEOUS_HPP

#include <GLFW/glfw3.h>
#include <iostream>

namespace HelperMiscellaneous {
	void PrintFps() {
		static float last = glfwGetTime();
		static int fps = 0;

		++fps;
		float now = glfwGetTime();
		if (now - last > .5) {
			std::cout << "\rFps: " << fps*2 << std::flush;
			last = now;
			fps = 0;
		}
	}
}

#endif //OPENGLPLAYGROUND_HELPERMISCELLANEOUS_HPP
