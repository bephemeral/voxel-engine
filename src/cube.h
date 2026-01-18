#pragma once
#include "vertex.h"

#include <glm/glm.hpp>

inline constexpr std::array<Vertex, 36> VERTICES{
    // Back face
    Vertex{-0.5f, -0.5f, -0.5f}, // Bottom-left
    Vertex{0.5f, 0.5f, -0.5f},   // Top-right
    Vertex{0.5f, -0.5f, -0.5f},  // Bottom-right
    Vertex{0.5f, 0.5f, -0.5f},   // Top-right
    Vertex{-0.5f, -0.5f, -0.5f}, // Bottom-left
    Vertex{-0.5f, 0.5f, -0.5f},  // Top-left

    // Front face
    Vertex{-0.5f, -0.5f, 0.5f}, // Bottom-left
    Vertex{0.5f, -0.5f, 0.5f},  // Bottom-right
    Vertex{0.5f, 0.5f, 0.5f},   // Top-right
    Vertex{0.5f, 0.5f, 0.5f},   // Top-right
    Vertex{-0.5f, 0.5f, 0.5f},  // Top-left
    Vertex{-0.5f, -0.5f, 0.5f}, // Bottom-left

    // Left face
    Vertex{-0.5f, 0.5f, 0.5f},   // Top-right
    Vertex{-0.5f, 0.5f, -0.5f},  // Top-left
    Vertex{-0.5f, -0.5f, -0.5f}, // Bottom-left
    Vertex{-0.5f, -0.5f, -0.5f}, // Bottom-left
    Vertex{-0.5f, -0.5f, 0.5f},  // Bottom-right
    Vertex{-0.5f, 0.5f, 0.5f},   // Top-right

    // Right face
    Vertex{0.5f, 0.5f, 0.5f},   // Top-left
    Vertex{0.5f, -0.5f, -0.5f}, // Bottom-right
    Vertex{0.5f, 0.5f, -0.5f},  // Top-right
    Vertex{0.5f, -0.5f, -0.5f}, // Bottom-right
    Vertex{0.5f, 0.5f, 0.5f},   // Top-left
    Vertex{0.5f, -0.5f, 0.5f},  // Bottom-left

    // Bottom face
    Vertex{-0.5f, -0.5f, -0.5f}, // Top-right
    Vertex{0.5f, -0.5f, -0.5f},  // Top-left
    Vertex{0.5f, -0.5f, 0.5f},   // Bottom-left
    Vertex{0.5f, -0.5f, 0.5f},   // Bottom-left
    Vertex{-0.5f, -0.5f, 0.5f},  // Bottom-right
    Vertex{-0.5f, -0.5f, -0.5f}, // Top-right

    // Top face
    Vertex{-0.5f, 0.5f, -0.5f}, // Top-left
    Vertex{0.5f, 0.5f, 0.5f},   // Bottom-right
    Vertex{0.5f, 0.5f, -0.5f},  // Top-right
    Vertex{0.5f, 0.5f, 0.5f},   // Bottom-right
    Vertex{-0.5f, 0.5f, -0.5f}, // Top-left
    Vertex{-0.5f, 0.5f, 0.5f}   // Bottom-left
};

inline constexpr glm::vec3 faceOffset[]{
    glm::vec3{0.0f, 0.0f, -1.0f}, // Back face
    glm::vec3{0.0f, 0.0f, 1.0f},  // Front face
    glm::vec3{-1.0f, 0.0f, 0.0f}, // Left face
    glm::vec3{1.0f, 0.0f, 0.0f},  // Right face
    glm::vec3{0.0f, -1.0f, 0.0f}, // Bottom face
    glm::vec3{0.0f, 1.0f, 0.0f}   // Top face
};