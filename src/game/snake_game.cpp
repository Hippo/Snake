#include "game/snake_game.hpp"

#include <chrono>
#include <queue>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static std::queue<int> s_KeyQueue;

#define MILLIS() std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()

Game::Game() :
    m_Window(800, 600, "Snake"),
    m_Shader("assets/shader/shader.vert", "assets/shader/shader.frag") {
}

void Game::run() {
    float width = static_cast<float>(m_Window.width()) / 10.0f;
    float height = static_cast<float>(m_Window.height()) / 10.0f;

    glm::vec4 border = glm::vec4(width / -2.0f, height / -2.0f, width / 2.0f,  height / 2.0f);
    m_Snake.setBorder(border);
    m_Snake.spawnApple();

    m_Shader.bind();
    glm::mat4 projection = glm::ortho(width / -2.0f, width / 2.0f, height / -2.0f, height / 2.0f);
    GLuint projectionMatrix = m_Shader.getUniformLocation("projectionMatrix");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(projection));

    m_Window.setKeyPressCallback(onKeyPress);

    constexpr int delay = 1000 / 15;
    long last = MILLIS();

    while (!m_Window.shouldClose()) {
        long now = MILLIS();

        if (now - last >= delay) {
            update();
            last = now;
        }

        render();
        m_Window.swapBuffers();
        Window::pollEvents();
    }
}

void Game::update() {
    if (!s_KeyQueue.empty()) {
        int key = s_KeyQueue.front();
        s_KeyQueue.pop();

        m_Snake.handleKeyPress(key);
    }
    m_Snake.update();
}

void Game::render() const {
    glClear(GL_COLOR_BUFFER_BIT);
    m_Snake.render(m_Shader);
}

void Game::onKeyPress(GLFWwindow*, int key, int, int action, int) {
    if (action == GLFW_PRESS) {
        switch (key) { //NOLINT
            case GLFW_KEY_UP:
            case GLFW_KEY_DOWN:
            case GLFW_KEY_LEFT:
            case GLFW_KEY_RIGHT:
                s_KeyQueue.push(key);
               break;
        }
    }
}