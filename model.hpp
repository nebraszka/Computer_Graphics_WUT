#pragma once

#include <glm/glm.hpp>

const float verticesWithColors[] = {
        // positions          // colors
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // green, front
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // red, back
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // blue, left
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, // yellow, right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, // purple, bottom
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f, // orange, top
        0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f,
};

const std::vector<glm::vec4> frontVertices = {
        glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
        glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f)};

const std::vector<glm::vec4> backVertices = {
        glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f)};

const std::vector<glm::vec4> leftVertices = {
        glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
        glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f)};

const std::vector<glm::vec4> rightVertices = {
        glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
        glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(0.5f, -0.5f, 0.5f, 1.0f)};

const std::vector<glm::vec4> bottomVertices = {
        glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
        glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f)};

const std::vector<glm::vec4> topVertices = {
        glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f)};

// world space positions of our cubes
glm::vec4 cubeTranslAngle[] = {
        glm::vec4(0.0f, 0.0f, -15.0f, 0.0f),
        glm::vec4(2.0f, 5.0f, -15.0f, 100.0f),
        glm::vec4(-1.5f, -2.2f, -2.5f, 40.0f),
        glm::vec4(-3.8f, -2.0f, -12.3f, 60.0f),
        glm::vec4(2.4f, -0.4f, -3.5f, 80.0f),
        glm::vec4(-1.7f, 3.0f, -7.5f, 100.0f),
        glm::vec4(1.3f, -2.0f, -2.5f, 120.0f),
        glm::vec4(1.5f, 2.0f, -2.5f, 140.0f),
        glm::vec4(1.5f, 0.2f, -1.5f, 160.0f),
        glm::vec4(-1.3f, 1.0f, -1.5f, 180.0f)
};
