#ifndef SNAKE_VERTEX_BUFFER_HPP
#define SNAKE_VERTEX_BUFFER_HPP

#include <cstdint>
#include <cstddef>

class VertexBuffer {
public:
    VertexBuffer(const void* vertices, size_t size, const uint32_t* indices, size_t indexCount);

    VertexBuffer(VertexBuffer&& other) noexcept;

    ~VertexBuffer();
    void bind() const;
    void draw() const;
    static void defineAttribute(int index, int size, uint32_t type, int32_t stride, size_t offest);
private:
    uint32_t m_Vao, m_Vbo, m_Ebo;
    size_t m_IndexCount;
};

#endif //SNAKE_VERTEX_BUFFER_HPP
