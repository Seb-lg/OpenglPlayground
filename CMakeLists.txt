cmake_minimum_required(VERSION 3.18)
project(OpenGLPlayground)
set(CMAKE_MODULE_PATH /home/seub/perso/OpenglPlayground/cmake-gl)

set(CMAKE_CXX_STANDARD 20)

message("Generated with config types: ${CMAKE_MODULE_PATH}")

find_package(glfw3)
find_package(Threads)
find_package(OpenGL)

add_executable(OpenglPlayground
        Main.cpp

        src/OpenGLWindow.cpp
        src/OpenGLWindow.hpp
        src/Textures.cpp
        src/Textures.hpp
        src/objs/Renderable.hpp
        src/objs/Renderable.cpp
        src/SceneTree.cpp
        src/SceneTree.hpp

        helpers/stb_image.hpp
        helpers/stb_image_writer.hpp
        helpers/HelperFile.hpp
        helpers/PerlinNoise.hpp
        helpers/HelperMiscellaneous.hpp
        src/Object.cpp src/Object.hpp helpers/YOLO.cpp helpers/YOLO.hpp src/PerlinMap.cpp src/PerlinMap.hpp src/objs/Chunk.cpp src/objs/Chunk.hpp)

target_link_libraries(OpenglPlayground ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(OpenglPlayground glfw ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})

find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(OpenglPlayground ${GLEW_LIBRARIES})
endif()
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
    target_link_libraries(OpenglPlayground ${GLM_LIBRARIES})
endif()
