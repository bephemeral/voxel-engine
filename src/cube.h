#pragma once
#include "vertex.h"

#include <glm/glm.hpp>

inline constexpr float TOP_FACE_BRIGNTESS{1.0f};
inline constexpr float BRIGHTNESS{0.8f};

inline constexpr std::array<Vertex, 36> VERTICES{
    // Back face
    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Bottom-left
    Vertex{glm::vec3(0.5f, 0.5f, -0.5f), BRIGHTNESS},   // Top-right
    Vertex{glm::vec3(0.5f, -0.5f, -0.5f), BRIGHTNESS},  // Bottom-right
    Vertex{glm::vec3(0.5f, 0.5f, -0.5f), BRIGHTNESS},   // Top-right
    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Bottom-left
    Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), BRIGHTNESS},  // Top-left

    // Front face
    Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), BRIGHTNESS}, // Bottom-left
    Vertex{glm::vec3(0.5f, -0.5f, 0.5f), BRIGHTNESS},  // Bottom-right
    Vertex{glm::vec3(0.5f, 0.5f, 0.5f), BRIGHTNESS},   // Top-right
    Vertex{glm::vec3(0.5f, 0.5f, 0.5f), BRIGHTNESS},   // Top-right
    Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), BRIGHTNESS},  // Top-left
    Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), BRIGHTNESS}, // Bottom-left

    // Left face
    Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), BRIGHTNESS},   // Top-right
    Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), BRIGHTNESS},  // Top-left
    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Bottom-left
    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Bottom-left
    Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), BRIGHTNESS},  // Bottom-right
    Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), BRIGHTNESS},   // Top-right

    // Right face
    Vertex{glm::vec3(0.5f, 0.5f, 0.5f), BRIGHTNESS},   // Top-left
    Vertex{glm::vec3(0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Bottom-right
    Vertex{glm::vec3(0.5f, 0.5f, -0.5f), BRIGHTNESS},  // Top-right
    Vertex{glm::vec3(0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Bottom-right
    Vertex{glm::vec3(0.5f, 0.5f, 0.5f), BRIGHTNESS},   // Top-left
    Vertex{glm::vec3(0.5f, -0.5f, 0.5f), BRIGHTNESS},  // Bottom-left

    // Bottom face
    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Top-right
    Vertex{glm::vec3(0.5f, -0.5f, -0.5f), BRIGHTNESS},  // Top-left
    Vertex{glm::vec3(0.5f, -0.5f, 0.5f), BRIGHTNESS},   // Bottom-left
    Vertex{glm::vec3(0.5f, -0.5f, 0.5f), BRIGHTNESS},   // Bottom-left
    Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), BRIGHTNESS},  // Bottom-right
    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BRIGHTNESS}, // Top-right

    // Top face
    Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), TOP_FACE_BRIGNTESS}, // Top-left
    Vertex{glm::vec3(0.5f, 0.5f, 0.5f), TOP_FACE_BRIGNTESS},   // Bottom-right
    Vertex{glm::vec3(0.5f, 0.5f, -0.5f), TOP_FACE_BRIGNTESS},  // Top-right
    Vertex{glm::vec3(0.5f, 0.5f, 0.5f), TOP_FACE_BRIGNTESS},   // Bottom-right
    Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), TOP_FACE_BRIGNTESS}, // Top-left
    Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), TOP_FACE_BRIGNTESS}   // Bottom-left
};

inline constexpr glm::vec3 faceOffset[]{
    glm::vec3{0.0f, 0.0f, -1.0f}, // Back face
    glm::vec3{0.0f, 0.0f, 1.0f},  // Front face
    glm::vec3{-1.0f, 0.0f, 0.0f}, // Left face
    glm::vec3{1.0f, 0.0f, 0.0f},  // Right face
    glm::vec3{0.0f, -1.0f, 0.0f}, // Bottom face
    glm::vec3{0.0f, 1.0f, 0.0f}   // Top face
};