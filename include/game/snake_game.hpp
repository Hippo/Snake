#ifndef SNAKE_SNAKE_GAME_HPP
#define SNAKE_SNAKE_GAME_HPP


#include "game/entity/snake.hpp"
#include "window/game_window.hpp"
#include "shader/shader.hpp"

class Game {
public:
    Game();

    void run();
    void update();
    void render() const;
    static void onKeyPress(GLFWwindow*, int key, int, int action, int);
private:
    Window m_Window;
    Shader m_Shader;
    Snake m_Snake;
};

#endif //SNAKE_SNAKE_GAME_HPP
