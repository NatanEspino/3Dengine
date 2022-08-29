#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    // Initialize GLFW
    glfwInit();

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Test", NULL, NULL);
    // Terminate window if it fails to initialize
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Add window to the current context
    glfwMakeContextCurrent(window);

    // Initialize glad
    gladLoadGL();

    // Specify OpenGL viewport
    glViewport(0, 0, 800, 800);

    // Specify background color, clear color buffer, and swapbuffers
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    // Main loop
    while (!glfwWindowShouldClose(window)){
        // Handle Events
        glfwPollEvents();
    }

    // Exit sequence
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
