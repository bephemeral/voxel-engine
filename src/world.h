#pragma once

#include "chunk.h"
#include "shader.h"
#include "PerlinNoise.hpp"

class World
{
public:
    World(siv::PerlinNoise::seed_type seed, int worldSizeChunks);

    void renderWorld(const Shader &shaderProgram) const;

private:
    std::vector<Chunk> chunks;
};

std::vector<Chunk> generateWorld(siv::PerlinNoise::seed_type seed, int worldSizeChunks);