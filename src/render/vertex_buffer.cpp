#include "render/vertex_buffer.hpp"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* vertices, size_t size, const uint32_t* indices, size_t indexCount) : m_IndexCount(indexCount) { //NOLINT
    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);

    glGenBuffers(1, &m_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept {
    m_Vao = other.m_Vao;
    m_Vbo = other.m_Vbo;
    m_Ebo = other.m_Ebo;
    m_IndexCount = other.m_IndexCount;

    other.m_Vao = -1;
    other.m_Vbo = -1;
    other.m_Ebo = -1;
    other.m_IndexCount = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
    if (this != &other) {
        m_Vao = other.m_Vao;
        m_Vbo = other.m_Vbo;
        m_Ebo = other.m_Ebo;
        m_IndexCount = other.m_IndexCount;

        other.m_Vao = -1;
        other.m_Vbo = -1;
        other.m_Ebo = -1;
        other.m_IndexCount = 0;
    }
    return *this;
}

VertexBuffer::~VertexBuffer() {
    if (m_Vao == -1 && m_Vbo == -1 && m_Ebo == -1) {
        glDeleteVertexArrays(1, &m_Vao);
        glDeleteBuffers(1, &m_Vbo);
        glDeleteBuffers(1, &m_Ebo);
    }
}

void VertexBuffer::bind() const {
    glBindVertexArray(m_Vao);
}

void VertexBuffer::draw() const {
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
}

void VertexBuffer::defineAttribute(int index, int size, uint32_t type, int32_t stride, size_t offest) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, reinterpret_cast<void*>(offest));
    glEnableVertexAttribArray(index);
}


