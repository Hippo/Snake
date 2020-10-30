#include "window/game_window.hpp"

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(const int width, const int height, const std::string_view& title) : m_Width(width), m_Height(height){
    if (glfwInit()) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_Window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        glfwSetWindowAspectRatio(m_Window, std::max(width, height), std::min(width, height));
        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD.");
        }

        glfwSetErrorCallback([](int,const char* message) {
            std::cerr << message << '\n';
        });

    } else {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize game window.");
    }
}

Window::~Window() {
    glfwTerminate();
}

void Window::swapBuffers() const {
    glfwSwapBuffers(m_Window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

int Window::width() const {
    return m_Width;
}

int Window::height() const {
    return m_Height;
}