#include "chunk.h"
#include "cube.h"

Chunk::Chunk(glm::vec3 pos, const siv::PerlinNoise &perlin) : position{pos}
{
    constexpr double SCALE = 0.05;
    constexpr int OCTAVES = 4;

    for (size_t i = 0; i < blocks.size(); ++i)
    {
        glm::vec3 blockPos = indexToPosition(i);

        double noise = perlin.octave2D(
            (pos.x + blockPos.x) * SCALE,
            (pos.z + blockPos.z) * SCALE,
            OCTAVES);

        noise = (noise + 1.0) * 0.5;
        int height = static_cast<int>(noise * CHUNK_SIZE);

        blocks[i] = (blockPos.y <= height);
    }
    generateMesh();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // setup vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Chunk::generateMesh()
{
    for (int x{0}; x < CHUNK_SIZE; ++x)
    {
        for (int y{0}; y < CHUNK_SIZE; ++y)
        {
            for (int z{0}; z < CHUNK_SIZE; ++z)
            {
                if (!isBlockSolid(x, y, z))
                    continue;

                for (int face{0}; face < 6; ++face)
                {
                    int nx{x + faceOffset[face].x};
                    int ny{y + faceOffset[face].y};
                    int nz{z + faceOffset[face].z};

                    if (!isBlockSolid(nx, ny, nz))
                    {
                        for (int i{0}; i < 6; ++i)
                        {
                            Vertex vertex{VERTICES[face * 6 + i]};
                            vertex.position += glm::vec3{x, y, z};

                            vertices.push_back(vertex);
                        }
                    }
                }
            }
        }
    }
}

void Chunk::renderMesh() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

inline glm::vec3 Chunk::indexToPosition(size_t index) const
{
    int x{index / (CHUNK_SIZE * CHUNK_SIZE)};
    index %= (CHUNK_SIZE * CHUNK_SIZE);

    int y{index / CHUNK_SIZE};
    int z{index % CHUNK_SIZE};
    return glm::vec3{x, y, z};
}

inline size_t Chunk::positionToIndex(int x, int y, int z) const
{
    return x * CHUNK_SIZE * CHUNK_SIZE + y * CHUNK_SIZE + z;
}

inline bool Chunk::isBlockSolid(int x, int y, int z) const
{
    if (x < 0 || x >= CHUNK_SIZE ||
        y < 0 || y >= CHUNK_SIZE ||
        z < 0 || z >= CHUNK_SIZE)
    {
        return false;
    }
    return blocks[positionToIndex(x, y, z)];
}