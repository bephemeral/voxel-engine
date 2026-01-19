#pragma once

#include "chunk.h"
#include "PerlinNoise.hpp"

std::vector<Chunk> generateWorld(siv::PerlinNoise::seed_type seed, int worldSizeChunks);