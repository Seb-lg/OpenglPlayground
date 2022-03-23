# OpenglPlayground
A personnal playground for opengl turning into submarine game.

## Story

A Barotrauma like game where the player start from the surface and descend to the center of the earth using a network of caves. \
The goal will be to reach the center of the planet while maintaining the submarine and upgrading it with found ores or the remains of past missions. 

- Start with an air drop ?

## TODO

- [X] Create a window 
- [X] Load and display an obj from file 
- [X] Add scene tree to the game engine
- [X] Use the scene tree to fix the position of the camera to the submarine
- [X] Use the perlin noise to generate a map around the submarine
- [X] Handle keyboard event
- [ ] Use multi-threading to generate map around player
- [ ] See if having only one vertex array is possible
- [ ] Create a shader to simulate the deep sea environment
- [ ] Create a lidar using ray-casting


## Reference
https://barotraumagame.com \
https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.3.camera_mouse_zoom/camera_mouse_zoom.cpp \
https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/7.in_practice/3.2d_game/0.full_source/shader.cpp \
https://github.com/Seb-lg/GameDesign/blob/935b584f41e534dd8b138d1596735345dfbe1b04/Source.cpp#L404