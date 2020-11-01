#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <cstdint>

#include <deque>
#include <list>

#include "game/vertex/game_vertex.hpp"
#include "render/vertex_buffer.hpp"
#include "shader/shader.hpp"

class Snake {
public:
    enum class Direction {
        NONE, UP, DOWN, LEFT, RIGHT
    };

    Snake();
    void progress(glm::ivec2 move);
    void handleKeyPress(int key);
    void update();
    void reset();
    void render(const Shader& shader) const;
    void setBorder(glm::vec4 border);
    void spawnApple();
private:
    std::deque<Vertex> m_Nodes;
    std::list<Vertex> m_Apples;
    VertexBuffer m_VertexBuffer;
    Direction m_Direction;
    int m_SkipTicks = 0;
    glm::vec4 m_Border;
};

#endif //SNAKE_SNAKE_HPP
