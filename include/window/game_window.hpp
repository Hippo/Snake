#ifndef SNAKE_GAME_WINDOW_HPP
#define SNAKE_GAME_WINDOW_HPP

#include <string_view>

#include <glm/glm.hpp>

struct GLFWwindow;

class Window {
public:
    Window(int width, int height, const std::string_view& title);
    ~Window();

    void swapBuffers() const;
    [[nodiscard]] bool shouldClose() const;
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;

    static void pollEvents();
private:
    GLFWwindow* m_Window;
    int m_Width;
    int m_Height;
};

#endif //SNAKE_GAME_WINDOW_HPP
