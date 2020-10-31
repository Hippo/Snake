#ifndef SNAKE_GAME_WINDOW_HPP
#define SNAKE_GAME_WINDOW_HPP

#include <functional>
#include <string_view>

#include <glm/glm.hpp>

struct GLFWwindow;

class Window {
public:
    Window(int width, int height, const std::string_view& title);
    ~Window();

    void swapBuffers() const;
    void setKeyPressCallback(void (*callback)(GLFWwindow*, int, int, int, int));
    [[nodiscard]] bool isKeyPressed(int key) const;
    [[nodiscard]] bool shouldClose() const;
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;

    static void pollEvents();
private:
    GLFWwindow* m_Window;
    std::function<void(int)> m_KeyCallback;
    int m_Width;
    int m_Height;
};

#endif //SNAKE_GAME_WINDOW_HPP
