#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GLuint loadShader(const char *path, GLenum type)
{
    // Read shader code from file path
    FILE *f;
    f = fopen(path, "r");

    int c;
    char *shaderCode;
    if (!f)
    {
        printf("Shader: Unable to open %s\n", path);
        printf("Terminating...\n");
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);
    
    if (!(shaderCode = malloc(fsize + 1)))
    {
        free(shaderCode);
        printf("Shader memory allocation failed!");
        return -1;
    }

    int i = 0;
    while ((c = fgetc(f)) != EOF)
    {
        shaderCode[i] = (char)c;
        i++;
    }
    shaderCode[i] = 0;
    fclose(f);

    // Create and compile shader
    GLuint Shader = glCreateShader(type);
    glShaderSource(Shader, 1, (const GLchar**)&shaderCode, NULL);
    glCompileShader(Shader);
    free(shaderCode);
    
    // Check for compilation errors
    GLint success;
    GLint maxLength = 512;
    GLchar log[maxLength];

    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(Shader, maxLength, NULL, log);
        printf("SHADER COMPILATION FAILED: \n%s", log);
        glDeleteShader(Shader);
        return -1;
    }

    return Shader;
}

int main()
{
    
    glfwInit();
    
    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
    // Terminate window if it fails to initialize
    if (window == NULL)
    {
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
    
    //Create vertex and fragment shaders
    GLuint vertexShader = loadShader("../vertexShader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader("../fragmentShader.glsl", GL_FRAGMENT_SHADER);

    // Attach shaders to shaderProgram
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check if program linked successfully
    GLint success;
    GLint maxLength = 512;
    char log[maxLength];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetProgramInfoLog(shaderProgram, maxLength, NULL, log);
        printf("Error while linking shader:\n%s", log);
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = 
    {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };    

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind buffers and vertex array
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Exit sequence
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
