/*
    "Virtual camera" program implemented as part of the Computer Graphics course
    at the Faculty of Electrical Engineering, Warsaw University of Technology. 
    
    Author: Maja Nagarnowicz (https://github.com/nebraszka)
*/

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>

#include <Shader.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

#define WINDOW_WIDTH 1000 
#define WINDOW_HEIGHT 800

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

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
 
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);

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

    // Set the vertex attributes pointers
    //  position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

    float i = -0.5f;

    // Show window
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        i = i - 0.01f;

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Change uniform color
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.0f) + 0.8f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        ourShader.use();

        /* NOTE: Remember that the actual transformation order should be read in reverse:
         * even though in code we first translate and then later rotate,
         * the actual transformations first apply a rotation and then a translation. 
         */ 

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, i));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        // Render triangles
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
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