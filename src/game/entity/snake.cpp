#include "game/entity/snake.hpp"

#include <array>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

struct SnakeVertex {
    glm::vec2 position;
    glm::vec3 color{0.0f, 1.0f, 0.0f};
};

inline VertexBuffer createVertexBuffer() {
    std::array<SnakeVertex, 4> vertices = {
            SnakeVertex{glm::vec2(0.5f, 0.5f)},
            SnakeVertex{glm::vec2(0.5f, -0.5f)},
            SnakeVertex{glm::vec2(-0.5f, -0.5f)},
            SnakeVertex{glm::vec2(-0.5f, 0.5f)}
    };

    std::array<uint32_t, 6> indices = {
            0, 1, 3, 1, 2, 3
    };


    VertexBuffer vertexBuffer(
            vertices.data(),
            sizeof(SnakeVertex) * vertices.size(),
            reinterpret_cast<const uint32_t*>(indices.data()),
            indices.size());
    VertexBuffer::defineAttribute(0, 2, GL_FLOAT, sizeof(SnakeVertex), 0);
    VertexBuffer::defineAttribute(1, 3, GL_FLOAT, sizeof(SnakeVertex), offsetof(SnakeVertex, color));
    return vertexBuffer;
}

Snake::Snake() : m_VertexBuffer(std::move(createVertexBuffer())) {

}


void Snake::progress(const glm::ivec2 move) {
    auto head = m_Nodes.back();
    auto tail = m_Nodes.front();
    m_Nodes.pop_back();
    m_Nodes.pop_front();

    tail.move(head.position());
    head.move(move);

    m_Nodes.push_back(tail);
    m_Nodes.push_back(head);
}
