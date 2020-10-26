#include <iostream>
#include <stdexcept>

#include "window/game_window.hpp"

int main() {
    try {
        Window(800, 600, "Snake").run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
