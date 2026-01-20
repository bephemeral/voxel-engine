#include "world.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline constexpr glm::mat4 IDENTITY_MATRIX{1.0f};

World::World(siv::PerlinNoise::seed_type seed, int worldSizeChunks, double scale, int octaves)
{
    const siv::PerlinNoise perlin{seed};

    for (int x = 0; x < worldSizeChunks; ++x)
    {
        for (int z = 0; z < worldSizeChunks; ++z)
        {
            chunks.emplace_back(glm::vec3(x * Chunk::CHUNK_SIZE, 0, z * Chunk::CHUNK_SIZE), perlin, scale, octaves);
        }
    }
}

void World::renderWorld(const Shader &shaderProgram) const
{
    for (const auto &chunk : chunks)
    {
        shaderProgram.setMat4("model", glm::translate(IDENTITY_MATRIX, chunk.position));
        chunk.renderMesh();
    }
}