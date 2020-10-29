#ifndef SNAKE_SHADER_HPP
#define SNAKE_SHADER_HPP

#include <cstdint>

#include <string_view>

class Shader {
public:
    Shader(const std::string_view& vertexPath, const std::string_view& fragmentPath);
    ~Shader();

    void use() const;
    int32_t getUniformLocation(const std::string_view& name) const;

private:
    uint32_t m_Id;
};

#endif //SNAKE_SHADER_HPP
