cmake_minimum_required(VERSION 3.13)

project(3Dengine)

find_package(glfw3 3.3 REQUIRED)

get_filename_component(PARENT_DIR ../ ABSOLUTE)

add_executable(${PROJECT_NAME} glad.c linearAlg.c main.c ${PARENT_DIR}/include/glad/glad.h ${PARENT_DIR}/include/linearAlg/linearAlg.h)

target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT_DIR}/include)

target_link_libraries(${PROJECT_NAME} glfw dl m)

