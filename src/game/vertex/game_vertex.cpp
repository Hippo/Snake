#include "game/vertex/game_vertex.hpp"


Vertex::Vertex(const glm::ivec2 position, const glm::vec3 color) : m_Position(position), m_Color(color) {

}

void Vertex::translate(const glm::ivec2 move) {
    m_Position += move;
}

void Vertex::move(const glm::ivec2 position) {
    m_Position = position;
}

bool Vertex::collides(const Vertex& vertex) const {
    return m_Position.x == vertex.m_Position.x && m_Position.y == vertex.m_Position.y;
}

glm::ivec2 Vertex::position() const {
    return m_Position;
}

glm::vec3 Vertex::color() const {
    return m_Color;
}

Vertex Vertex::makeSnakeVertex(glm::ivec2 position) {
    return Vertex(position, glm::vec3(0, 1, 0));
}

