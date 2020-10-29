#include "game/snake_game.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Game::Game() : m_Window(800, 600, "Snake"), m_Shader("assets/shader/shader.vert", "assets/shader/shader.frag") {
    const int width = m_Window.width();
    const int height = m_Window.height();

    m_Projection = glm::ortho(width / -2, width / 2, 0, height);
}

Game::~Game() {
}

void Game::run() {
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


}
