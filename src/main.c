#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linearAlg/linearAlg.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLuint loadShader(const char* path, GLenum type);
void handleInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLboolean firstMouse = GL_TRUE;
float lastX;
float lastY;
float mouseSensitivity;

float yaw = (float)(-PI / 2);
float pitch = 0.0f;
float cameraSpeed;
float fov = (float)(PI / 4);
float fps;

vec3 cameraFront;
vec3 cameraUp;
vec3 cameraRight;
vec3 cameraPosition = {{0.0f, 0.0f, 3.0f}};

int main(){
    glfwInit();

    // set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // create GLFW window
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
	const float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    // terminate window if it fails to initialize
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // add window to the current context
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scroll_callback); 

    // initialize glad
    gladLoadGL();

    glEnable(GL_DEPTH_TEST);

    // specify OpenGL viewport
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    
    // create vertex and fragment shaders
    GLuint vertexShader = loadShader("../shaders/vertexShader.vs", GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader("../shaders/fragmentShader.fs", GL_FRAGMENT_SHADER);

    // attach shaders to shaderProgram
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check if program linked successfully
    GLint success;
    GLint maxLength = 512;
    char log[maxLength];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (success == GL_FALSE){
        glGetProgramInfoLog(shaderProgram, maxLength, NULL, log);
        printf("Error while linking shader:\n%s", log);
    }

    // cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	
    // vertices
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
	
	vec3 cubePositions[10] = {
		{{ 0.0f, 0.0f,  0.0f}},
		{{ 2.0f, 5.0f,-15.0f}},
		{{-1.5f,-2.2f, -2.5f}},
		{{-3.8f,-2.0f,-12.3f}},
		{{ 2.4f,-0.4f, -3.5f}},
		{{-1.7f, 3.0f, -7.5f}},
		{{ 1.3f,-2.0f, -2.5f}},
		{{ 1.5f, 2.0f, -2.5f}},
		{{ 1.5f, 0.2f, -1.5f}},
		{{-1.3f, 1.0f, -1.5f}}
	};
	
    // create vertex array object, vertex and element buffer objects
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind and add data to array and buffer objects
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertexes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // tex coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load("../images/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture");
    }

    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    data = stbi_load("../images/chiaki.png", &width, &height, &nrChannels, 0);
    if (data) {
        // note that the png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	
    // rotation axis
	vec3 v = {{1.0f, 0.3f, 0.5f}};
	
    mat4 model = IDENTITY_MATRIX;
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, (const GLfloat *)&model.m);


    
    cameraFront.x = cosf(yaw) * cosf(pitch);
    cameraFront.y = sinf(pitch);
    cameraFront.z = sinf(yaw) * cosf(pitch); 
    cameraUp = jHat;
	
    mat4 view = lookAt(cameraPosition, addVec(cameraPosition, cameraFront), cameraUp);
	
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, (const GLfloat *)&view.m);
    
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    mat4 projection = perspective(fov, aspectRatio, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, (const GLfloat *)&projection.m);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // game variables
    float currentFrame, deltaTime;
    float lastFrame = 0.0f;
    
    // main loop
    while (!glfwWindowShouldClose(window)){
        
        currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        cameraSpeed = 2.5f * deltaTime;
        mouseSensitivity = 25.0f * deltaTime;
        cameraRight = crossProduct(cameraUp, cameraFront);
      
        handleInput(window);
        
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        
        projection = perspective(fov, aspectRatio, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, (const GLfloat *)&projection.m);   

		view = lookAt(cameraPosition, addVec(cameraPosition, cameraFront), cameraUp);
		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, (const GLfloat *)&view.m);
		
		for(unsigned int i = 0; i < 10; i++){
			model = IDENTITY_MATRIX;
			float angle = (float)(PI/9) * i;
			rotateMat4Axis(&model, v, angle);
			translate(&model, cubePositions[i]);
			glUniformMatrix4fv(modelLoc, 1, GL_TRUE, (const GLfloat *)&model.m);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}	
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    // Exit sequence
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

GLuint loadShader(const char *path, GLenum type){
    // read shader code from file path
    FILE *f;
    f = fopen(path, "r");

    int c;
    char *shaderCode;
    if (!f){
        printf("Shader: Unable to open %s\n", path);
        printf("Terminating...\n");
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);
    
    if (!(shaderCode = malloc(fsize + 1))){
        free(shaderCode);
        printf("Shader memory allocation failed!");
        return -1;
    }

    int i = 0;
    while ((c = fgetc(f)) != EOF){
        shaderCode[i] = (char)c;
        i++;
    }
    shaderCode[i] = 0;
    fclose(f);

    // create and compile shader
    GLuint Shader = glCreateShader(type);
    glShaderSource(Shader, 1, (const GLchar**)&shaderCode, NULL);
    glCompileShader(Shader);
    free(shaderCode);
    
    // check for compilation errors
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

void handleInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPosition = addVec(cameraPosition, scaleVec(cameraFront, cameraSpeed));
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPosition = addVec(cameraPosition, scaleVec(cameraFront, -cameraSpeed));
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPosition = addVec(cameraPosition, scaleVec(cameraRight, cameraSpeed));
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPosition = addVec(cameraPosition, scaleVec(cameraRight, -cameraSpeed)); 
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = (float)xposIn;
    float ypos = (float)yposIn;

    if (firstMouse == GL_TRUE){
        lastX = xpos;
        lastY = ypos;
        firstMouse = GL_FALSE;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= mouseSensitivity * cameraSpeed;
    yoffset *= mouseSensitivity * cameraSpeed;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > (float)(PI / 2))
        pitch = (float)(PI / 2);
    if (pitch < (float)(-PI / 2))
        pitch = (float)(-PI / 2);

    cameraFront.x = cosf(yaw) * cosf(pitch);
    cameraFront.y = sinf(pitch);
    cameraFront.z = sinf(yaw) * cosf(pitch);

    cameraUp.x = -cosf(yaw) * sinf(pitch);
    cameraUp.y = cosf(pitch);
    cameraUp.z = -sinf(yaw) * sinf(pitch);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    fov -= (float)yoffset * (float)(PI / 180);
    if (fov < (float)(PI / 180))
        fov = (float)(PI / 180);
    if (fov > (float)(PI / 4))
        fov = (float)(PI / 4); 
}