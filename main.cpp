/*
    "Virtual camera" program implemented as part of the Computer Graphics course
    at the Faculty of Electrical Engineering, Warsaw University of Technology. 
    
    Author: Maja Nagarnowicz (https://github.com/nebraszka)
*/

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#include <Shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

#define WINDOW_WIDTH 800 
#define WINDOW_HEIGHT 600

int main()
{
    /*
     *  Note:
     *  GLFW is a library, written in C, specifically targeted at OpenGL.
     *  GLFW gives us the bare necessities required for rendering goodies to the screen.
     *  It allows us to create an OpenGL context, define window parameters, 
     *  and handle user input, which is plenty enough for our purposes. 
     * 
     *  Source: https://learnopengl.com/Getting-started/Creating-a-window
     */

    // Configuration of GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creation of GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
                                            "Virtual Camera by Maja Nagarnowicz", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD loads function pointers for OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    // TODO: Change it! It cannot be hardcoded!
    Shader ourShader("/home/nebraszka/GITHUB/computer_graphics_pw/vertexShader.vs", "/home/nebraszka/GITHUB/computer_graphics_pw/frameShader.fs");

    // ---------------------------------------------------------------------------

    float vertices[] = {
        // positions        //colors
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  
    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* Binding Vertex Array Object (VAO)
     *
     * This has the advantage that when configuring vertex attribute pointers
     * you only have to make those calls once and whenever we want to draw the object,
     * we can just bind the corresponding VAO
     * 
     * Source: https://learnopengl.com/Getting-started/Hello-Triangle
     */
    glBindVertexArray(VAO);

    /* Loading the vertices into Vertex Buffer Objects (VBO)
     *
     * We manage this memory via so called vertex buffer objects (VBO)
     * that can store a large number of vertices in the GPU's memory. 
     * The advantage of using those buffer objects is that we can send 
     * large batches of data all at once to the graphics card, 
     * and keep it there if there's enough memory left, 
     * without having to send data one vertex at a time.
     * 
     * Source: https://learnopengl.com/Getting-started/Hello-Triangle
     */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* An EBO (element buffer objects) is a buffer, 
     * just like a vertex buffer object, that stores indices 
     * that OpenGL uses to decide what vertices to draw. 
     */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set the vertex attributes pointers
    //  position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //  color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    /* note that this is allowed, 
     * the call to glVertexAttribPointer registered VBO
     * as the vertex attribute's bound vertex buffer object
     * so afterwards we can safely unbind
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);  
    
    /*
     *  Note:
     *  Modern OpenGL requires that we at least set up a vertex and 
     *  fragment shader if we want to do some rendering
     * 
     *  Source: https://learnopengl.com/Getting-started/Hello-Triangle
     */

    // On window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    // Wireframe mode activated
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Show window
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); 

        // Change uniform color
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.0f) + 0.8f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        ourShader.use();
        
        // Render triangles
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // There are 2 buffers - back and front buffer
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

// Resize viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

// Control input
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}