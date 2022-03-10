//
// Created by seub on 3/10/22.
//

#include <iostream>
#include "src/OpenGLWindow.hpp"
#include "src/Textures.hpp"

int main(){
    std::cout << "Hello OpenGl" << std::endl;
    OpenGLWindow window;

    //  Load Textures
    Textures textures;
    textures["./assets/awesomeface.bmp"];
    textures["./assets/container.bmp"];


    std::cout << "\nEnd of initialisation..." << std::endl;
    while(window.update()){

    }
}