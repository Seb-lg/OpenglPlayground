//
// Created by seub on 3/20/22.
//

#ifndef OPENGLPLAYGROUND_HELPERMISCELLANEOUS_HPP
#define OPENGLPLAYGROUND_HELPERMISCELLANEOUS_HPP

#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

namespace HelperMiscellaneous {
	static void PrintFps() {
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

	static void PrintProgress(float progress) {
		std::cout << "[";
		int pos = 100 * progress;
		for (int i = 0; i < 100; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		std::cout << "] " << int(progress * 100.0) << " %\r";
		std::cout.flush();
	}

	static glm::vec4 StringToColor(std::string color, bool print = false) {
		if (color[0] == '#')
			color.erase(0,1);
		int r,g,b;
		std::istringstream(color.substr(0,2)) >> std::hex >> r;
		std::istringstream(color.substr(2,2)) >> std::hex >> g;
		std::istringstream(color.substr(4,2)) >> std::hex >> b;

		glm::vec4 out = {(float)(r)/255.f, (float)(g)/255.f, (float)(b)/255.f, 1.f};
		if (print)
			std::cout << out[0] << '\t' << out[1] << '\t' << out[2] << '\t' << out[3] << std::endl;
		return out;
	}

}

#endif //OPENGLPLAYGROUND_HELPERMISCELLANEOUS_HPP
