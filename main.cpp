/*
    "Virtual camera" program implemented as part of the Computer Graphics course
    at the Faculty of Electrical Engineering, Warsaw University of Technology.

    Author: Maja Nagarnowicz (https://github.com/nebraszka)
*/

#define GLM_SWIZZLE

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

#include <painterAlgorithm.hpp>
#include <Shader.hpp>
#include <model.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// camera - start position
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool compareDistance(const glm::vec3 &a, const glm::vec3 &b) {
    return glm::length(cameraPos - a) > glm::length(cameraPos - b);
}

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;
float pitch = 0.0f;

int main() {
    // Configuration of GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creation of GLFW window
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Virtual Camera by Maja Nagarnowicz", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // On window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD loads function pointers for OpenGL
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // TODO: Change it! It cannot be hardcoded!
    Shader ourShader("/home/nebraszka/CLionProjects/computer_graphics_pw/vertexShader.vs",
                     "/home/nebraszka/CLionProjects/computer_graphics_pw/fragmentShader.fs");

    // ---------------------------------------------------------------------------

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Binding Vertex Array Object (VAO)
    glBindVertexArray(VAO);

    // Loading the vertices into Vertex Buffer Objects (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesWithColors), verticesWithColors, GL_STATIC_DRAW);

    // Set the vertex attributes pointers
    //  position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    //  color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindVertexArray(VBO);

//    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_NEVER);

//    // Wireframe mode activated
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::mat4 view;

    // Show window
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        std::sort(cubeTranslAngle, cubeTranslAngle + 10, compareDistance);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

        ourShader.use();

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(fov), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Render triangles
        glBindVertexArray(
                VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        for (auto &translAngle: cubeTranslAngle) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, translAngle.xyz());
            float angle = translAngle[3];
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glm::mat4 transform = model;
            std::vector<int> results = getIndexesOrder(transform, cameraPos);

            for (auto &index: results) {
                glDrawArrays(GL_TRIANGLES, index, 6);
            }
        }

        // There are 2 buffers - back and front buffer
        glfwSwapBuffers(window);
        // Check if any events are triggered
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Resize viewport
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Control input
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraUp = glm::rotate(cameraUp, glm::radians(1.0f), cameraFront);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        cameraUp = glm::rotate(cameraUp, glm::radians(-1.0f), cameraFront);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        cameraFront = glm::rotate(cameraFront, glm::radians(1.0f), cameraUp);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        cameraFront = glm::rotate(cameraFront, glm::radians(-1.0f), cameraUp);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {

        pitch += 1.0f;
        if (pitch > 89.0f) {
            pitch = 89.0f;
            return;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
            return;
        }

        cameraFront = glm::rotate(cameraFront, glm::radians(1.0f), glm::normalize(glm::cross(cameraFront, cameraUp)));
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {

        pitch -= 1.0f;
        if (pitch > 89.0f) {
            pitch = 89.0f;
            return;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
            return;
        }

        cameraFront = glm::rotate(cameraFront, glm::radians(-1.0f), glm::normalize(glm::cross(cameraFront, cameraUp)));
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    pitch += yoffset;

    cameraFront = glm::rotate(cameraFront, glm::radians(-xoffset), cameraUp);

    cameraFront = glm::rotate(cameraFront, glm::radians(yoffset), glm::normalize(glm::cross(cameraFront, cameraUp)));
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    fov -= (float) yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
