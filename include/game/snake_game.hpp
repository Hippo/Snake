#ifndef SNAKE_SNAKE_GAME_HPP
#define SNAKE_SNAKE_GAME_HPP

#include "window/game_window.hpp"
#include "shader/shader.hpp"

class Game {
public:
    Game();
    ~Game();

    void run();
    void update() const;
    void render() const;

private:
    Window m_Window;
    Shader m_Shader;
    glm::mat4 m_Projection;

};

#endif //SNAKE_SNAKE_GAME_HPP
