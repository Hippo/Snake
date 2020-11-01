#include "game/entity/snake.hpp"

#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

inline VertexBuffer createVertexBuffer() {
    glm::vec2 vertices[] = {
            glm::vec2(0.4f, 0.4f),
            glm::vec2(0.4f, -0.4f),
            glm::vec2(-0.4f, -0.4f),
            glm::vec2(-0.4f, 0.4f)
    };

    uint32_t indices[] = {
            0, 1, 3, 1, 2, 3
    };


    VertexBuffer vertexBuffer(
            vertices,
            sizeof(glm::vec2) * 4,
            indices,
            6);

    VertexBuffer::defineAttribute(0, 2, GL_FLOAT, sizeof(glm::vec2), 0);
    return vertexBuffer;
}


Snake::Snake() : m_VertexBuffer(std::move(createVertexBuffer())), m_Direction(Direction::NONE) {
    reset();
}

void Snake::progress(const glm::ivec2 move) {
    auto head = m_Nodes.back();
    m_Nodes.pop_back();

    glm::ivec2 originalHead = head.position();

    head.translate(move);

    float minX = m_Border.x;
    float minY = m_Border.y;
    float maxX = m_Border.z;
    float maxY = m_Border.w;

    glm::vec2 position = head.position();


    if (position.x > maxX) {
        position.x = minX;

    } else if (position.x < minX) {
        position.x = maxX;
    }


    if (position.y > maxY) {
        position.y = minY;
    } else if (position.y < minY) {
        position.y = maxY;
    }

    head.move(glm::ivec2(position.x, position.y));

    int removed = 0;
    for (auto it = m_Apples.begin(); it != m_Apples.end(); it++) {
        if (it->collides(head)) {
            m_Apples.erase(it--);
            removed++;
        }
    }
    for (int i = 0; i < removed; i++) {
        spawnApple();
    }

    if (removed > 0) {
        m_Nodes.push_back(Vertex::makeSnakeVertex(originalHead));
    } else {
        auto tail = m_Nodes.front();
        m_Nodes.pop_front();
        tail.move(originalHead);
        m_Nodes.push_back(tail);
    }


    for (const auto& node : m_Nodes) {
        if (head.collides(node)) {
            reset();
            return;
        }
    }


    m_Nodes.push_back(head);

}

void Snake::render(const Shader& shader) const {
    shader.bind();
    m_VertexBuffer.bind();

    GLuint modelMatrix = shader.getUniformLocation("modelMatrix");
    GLuint color = shader.getUniformLocation("color");
    for (const auto& node : m_Nodes) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(node.position(), 0.0f));
        glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(color, 1, glm::value_ptr(node.color()));

        m_VertexBuffer.draw();
    }

    for (const auto& apple : m_Apples) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(apple.position(), 0.0f));
        glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(color, 1, glm::value_ptr(apple.color()));

        m_VertexBuffer.draw();
    }

}

void Snake::handleKeyPress(int key) {
    switch (key) { //NOLINT
        case GLFW_KEY_UP:
            if (m_Direction != Direction::DOWN) {
                progress(glm::ivec2(0, 1));
                m_Direction = Direction::UP;
                m_SkipTicks++;
            }
            break;

        case GLFW_KEY_DOWN:
            if (m_Direction != Direction::UP) {
                progress(glm::ivec2(0, -1));
                m_Direction = Direction::DOWN;
                m_SkipTicks++;
            }
            break;

        case GLFW_KEY_LEFT:
            if (m_Direction != Direction::RIGHT) {
                progress(glm::ivec2(-1, 0));
                m_Direction = Direction::LEFT;
                m_SkipTicks++;
            }
            break;

        case GLFW_KEY_RIGHT:
            if (m_Direction != Direction::LEFT) {
                progress(glm::ivec2(1, 0));
                m_Direction = Direction::RIGHT;
                m_SkipTicks++;
            }
            break;
    }
}

void Snake::update() {
    if (m_SkipTicks > 0) {
        m_SkipTicks--;
    } else {
        switch (m_Direction) {
            case Direction::NONE:
                break;
            case Direction::UP:
                progress(glm::ivec2(0, 1));
                break;
            case Direction::DOWN:
                progress(glm::ivec2(0, -1));
                break;
            case Direction::LEFT:
                progress(glm::ivec2(-1, 0));
                break;
            case Direction::RIGHT:
                progress(glm::ivec2(1, 0));
                break;
        }
    }
}

void Snake::reset() {
    m_Nodes.clear();
    m_Direction = Direction::NONE;
    m_SkipTicks = 0;
    int i;
    for (i = 0; i < 3; i++) {
        m_Nodes.push_back(Vertex::makeSnakeVertex(glm::ivec2(0, i)));
    }
    m_Nodes.emplace_back(glm::ivec2(0, i), glm::vec3(1, 1, 1));
}

void Snake::setBorder(glm::vec4 border) {
    m_Border = border;
}

void Snake::spawnApple() {
    float minX = m_Border.x;
    float minY = m_Border.y;
    float maxX = m_Border.z;
    float maxY = m_Border.w;

    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_real_distribution<float> xDistribution(minX, maxX);
    std::uniform_real_distribution<float> yDistribution(minY, maxY);

    float x = xDistribution(mt);
    float y = yDistribution(mt);

    bool valid = false;

    while (!valid) {
        bool pass = true;

        for (const auto& node : m_Nodes) {
            glm::ivec2 position = node.position();
            if (position.x == x && position.y == y) {
                pass = false;
                break;
            }
        }

        if (pass) {
            for (const auto& apple : m_Apples) {
                glm::ivec2 position = apple.position();
                if (position.x == x && position.y == y) {
                    pass = false;
                    break;
                }
            }
        }

        if (!pass) {
            x = xDistribution(mt);
            y = yDistribution(mt);
        }

        valid = pass;
    }

    m_Apples.emplace_back(glm::ivec2(x, y), glm::vec3(1, 0, 0));
}
