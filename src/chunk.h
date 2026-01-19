#pragma once
#include "vertex.h"

#include "PerlinNoise.hpp"
#include <array>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Chunk
{
public:
    static inline constexpr size_t CHUNK_SIZE{16};

    glm::vec3 position;
    std::array<bool, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE> blocks{};
    std::vector<Vertex> vertices;

    Chunk(glm::vec3 pos, const siv::PerlinNoise &perlin);

    void generateMesh();
    void renderMesh() const;

private:
    GLuint VBO;
    GLuint VAO;

    inline glm::vec3 indexToPosition(size_t index) const;
    inline size_t positionToIndex(int x, int y, int z) const;
    inline bool isBlockSolid(int x, int y, int z) const;
};