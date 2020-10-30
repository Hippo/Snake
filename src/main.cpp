#include <iostream>
#include <stdexcept>

#include "game/snake_game.hpp"


int main() {
    try {
        Game().run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
