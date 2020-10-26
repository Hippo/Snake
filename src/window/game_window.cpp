#include <stdexcept>

#include "window/game_window.hpp"


Window::Window(const int width, const int height, const char *title) {
    m_Game = new Game();

    if (glfwInit()) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD.");
        }

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow*, int width, int height) {
            glViewport(0, 0, width, height);
        });
    } else {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize game window.");
    }
}

Window::~Window() {
    delete m_Game;
    glfwTerminate();
}

void Window::run() const {
    while (!glfwWindowShouldClose(m_Window)) {
        m_Game->update();
        m_Game->render();
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
