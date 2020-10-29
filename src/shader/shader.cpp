#include "shader/shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

void createShader(GLuint &shader, const char *source, const int shaderType) {
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int flag;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &flag);
    if (!flag) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &flag);
        char infoLog[flag];
        glGetShaderInfoLog(shader, flag, &flag, infoLog);
        throw std::runtime_error(infoLog);
    }
}


Shader::Shader(const std::string_view& vertexPath, const std::string_view& fragmentPath) {
    std::ifstream vertexStream(vertexPath);
    std::ifstream fragmentStream(fragmentPath);

    std::string vertexCode((std::istreambuf_iterator<char>(vertexStream)), std::istreambuf_iterator<char>());
    std::string fragmentCode((std::istreambuf_iterator<char>(fragmentStream)), std::istreambuf_iterator<char>());

    GLuint vertex, fragment;
    createShader(vertex, vertexCode.c_str(), GL_VERTEX_SHADER);
    createShader(fragment, fragmentCode.c_str(), GL_FRAGMENT_SHADER);


    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertex);
    glAttachShader(m_Id, fragment);
    glLinkProgram(m_Id);

    int flag;
    glGetProgramiv(m_Id, GL_LINK_STATUS, &flag);
    if (!flag) {
        glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &flag);
        char infoLog[flag];
        glGetProgramInfoLog(m_Id, flag, &flag, infoLog);
        throw std::runtime_error(infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

Shader::~Shader() {
    glDeleteProgram(m_Id);
}

void Shader::use() const {
    glUseProgram(m_Id);
}

GLint Shader::getUniformLocation(const std::string_view& name) const {
    return glGetUniformLocation(m_Id, name.data());
}
