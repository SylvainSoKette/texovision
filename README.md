# Tex-O-Vision

A procedural texture generator and visualizer.

## Requirements

- GNU Make 4.2.1+
- gcc 9.3+
- SDL2 (```apt install libsdl2-dev```)
- GLEW (```apt install libglew-dev```)
- glm (```apt install libglm-dev```)

## Make recipes

- ```make all``` (default recipe): compile everything
- ```make run``` : compiles everything and run the program
- ```make clean``` : remove all temporary build files from the project
- ```make purge``` : removes compiled program, imgui.ini and temporary build files
