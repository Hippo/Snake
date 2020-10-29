#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <deque>

#include "game/vertex/game_vertex.hpp"
#include "render/vertex_buffer.hpp"

class Snake {
public:
    Snake();
    void progress(const glm::ivec2 move);
private:
    std::deque<Vertex> m_Nodes;
    VertexBuffer m_VertexBuffer;
};

#endif //SNAKE_SNAKE_HPP
