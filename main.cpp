/*
    "Virtual camera" program implemented as part of the Computer Graphics course
    at the Faculty of Electrical Engineering, Warsaw University of Technology. 
    
    Author: Maja Nagarnowicz (https://github.com/nebraszka)
*/

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define WINDOW_WIDTH 800 
#define WINDOW_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    /*
        Note:
        GLFW is a library, written in C, specifically targeted at OpenGL.
        GLFW gives us the bare necessities required for rendering goodies to the screen.
        It allows us to create an OpenGL context, define window parameters, 
        and handle user input, which is plenty enough for our purposes. 

        Source: https://learnopengl.com/Getting-started/Creating-a-window
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

    // On window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    // Show window
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        //Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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