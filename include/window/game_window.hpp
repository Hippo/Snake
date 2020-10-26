#ifndef SNAKE_GAME_WINDOW_HPP
#define SNAKE_GAME_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/snake_game.hpp"

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();
    void run() const;
protected:
    GLFWwindow* m_Window;
    Game* m_Game;
};

#endif //SNAKE_GAME_WINDOW_HPP
