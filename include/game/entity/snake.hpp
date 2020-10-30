#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <deque>

#include "game/vertex/game_vertex.hpp"
#include "render/vertex_buffer.hpp"
#include "shader/shader.hpp"

class Snake {
public:
    Snake();
    void progress(glm::ivec2 move);
    void render(const Shader& shader) const;
private:
    std::deque<Vertex> m_Nodes;
    VertexBuffer m_VertexBuffer;
};

#endif //SNAKE_SNAKE_HPP
