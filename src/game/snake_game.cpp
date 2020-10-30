#include "game/snake_game.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game() :
    m_Window(800, 600, "Snake"),
    m_Shader("assets/shader/shader.vert", "assets/shader/shader.frag") {
}

Game::~Game() {
}


void Game::run() {
    float width = m_Window.width();
    float height = m_Window.height();

    m_Shader.bind();
    glm::mat4 projection = glm::ortho(width / -2.0f, width / 2.0f, height / -2.0f, height / 2.0f);
    GLuint projectionMatrix = m_Shader.getUniformLocation("projectionMatrix");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(projection));


    while (!m_Window.shouldClose()) {
        render();
        m_Window.swapBuffers();
        Window::pollEvents();
    }
}

void Game::update() const {
}

void Game::render() const {
    glClear(GL_COLOR_BUFFER_BIT);
    m_Snake.render(m_Shader);
    GLint error = glGetError();
    if (error) {
        std::cout << error << '\n';
    }
}
