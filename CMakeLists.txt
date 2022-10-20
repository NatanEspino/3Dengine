cmake_minimum_required(VERSION 3.17)

project(Raycaster)

find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} glad.c linearAlg.c main.c)

target_link_libraries(${PROJECT_NAME} glfw)

