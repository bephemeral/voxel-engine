#include "world.h"

std::vector<Chunk> generateWorld(siv::PerlinNoise::seed_type seed, int worldSizeChunks)
{
    const siv::PerlinNoise perlin{seed};

    std::vector<Chunk> chunks;
    for (int x = 0; x < worldSizeChunks; ++x)
    {
        for (int z = 0; z < worldSizeChunks; ++z)
        {
            chunks.emplace_back(glm::vec3(x * Chunk::CHUNK_SIZE, 0, z * Chunk::CHUNK_SIZE), perlin);
        }
    }

    return chunks;
}