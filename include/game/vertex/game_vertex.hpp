#ifndef SNAKE_GAME_VERTEX_HPP
#define SNAKE_GAME_VERTEX_HPP

#include <glm/glm.hpp>

class Vertex {
public:
    Vertex(glm::ivec2 position, glm::vec3 color);

    void translate(glm::ivec2 move);
    void move(glm::ivec2 position);

    [[nodiscard]] bool collides(const Vertex& vertex) const;
    [[nodiscard]] glm::ivec2 position() const;
    [[nodiscard]] glm::vec3  color() const;

    static Vertex makeSnakeVertex(glm::ivec2 position);

private:
    glm::ivec2 m_Position{};
    glm::vec3 m_Color{};
};

#endif //SNAKE_GAME_VERTEX_HPP
