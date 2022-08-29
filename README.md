# Raycaster
Just a small little program messing around with Opengl and C

# Build Instructions:

# Linux

Dependencies:
glfw
glad

Make sure you have GLFW package installed on your system.
This project uses the OpenGL 3.3 core profile so make sure you install a glad api with gl 3.3 or higher and profile set to core. Make sure glad.h is in /usr/include and glad.c is in the source folder alongside main.c.

# Compiling the program
Use the inlcuded CMakeLists.txt to generate makefile and then use make

Commands:
cmake -S . -B build
cd build
make
