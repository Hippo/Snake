#include "game/entity/snake.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

inline VertexBuffer createVertexBuffer() {
    glm::vec2 vertices[] = {
            glm::vec2(0.5f, 0.4f),
            glm::vec2(0.5f, -0.5f),
            glm::vec2(-0.5f, -0.5f),
            glm::vec2(-0.5f, 0.4f)
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

Snake::Snake() : m_VertexBuffer(std::move(createVertexBuffer())) {
    for (int i = 0; i < 3; i++) {
        m_Nodes.push_back(Vertex::makeSnakeVertex(glm::ivec2(0, i)));
    }
}
#include <iostream>

void Snake::progress(const glm::ivec2 move) {
    auto head = m_Nodes.back();
    auto tail = m_Nodes.front();
    m_Nodes.pop_back();
    m_Nodes.pop_front();


    std::cout << tail.position().x << " " << tail.position().y << " | " << head.position().x << " " << head.position().y << std::endl;
    tail.move(head.position());
    head.translate(move);
    std::cout << tail.position().x << " " << tail.position().y << " | " << head.position().x << " " << head.position().y << std::endl;


    m_Nodes.push_back(tail);
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
        glUniform3f(color, 0.0f, 1.0f, 0.0f);

        m_VertexBuffer.draw();
    }
}
