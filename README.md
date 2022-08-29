# Raycaster
Just a small little program messing around with Opengl and C

# Build Instructions:

# Linux

Dependencies:
glfw
glad

Make sure you have GLFW package installed on your system, if installed correctly there should be a folder called GLFW in /usr/include containing glfw3.h and glfw3native.h
This project uses the OpenGL 3.3 core profile so make sure you install a glad api with gl 3.3 or higher and profile set to core. Make sure glad.h is in /usr/include.

# Compiling the program
Use the inlcuded CMakeLists.txt to generate makefile and then use make

Commands:
cmake -S . -B build
cd build
make
