# Project meta
cmake_minimum_required(VERSION 3.17)
project(Snake)
set(CMAKE_CXX_STANDARD 17)

# Find OpenGL package (required)
find_package(OpenGL REQUIRED)

# Add our git submodules subdirectory
add_subdirectory(vendors/glfw)
add_subdirectory(vendors/glm)

# Include our include folder
include_directories(include)

# Add our executable files
add_executable(Snake src/main.cpp src/window/game_window.cpp include/window/game_window.hpp include/game/snake_game.hpp src/game/snake_game.cpp include/game/entity/snake.hpp include/shader/shader.hpp src/shader/shader.cpp include/game/vertex/game_vertex.hpp src/game/vertex/game_vertex.cpp src/game/entity/snake.cpp include/render/vertex_buffer.hpp src/render/vertex_buffer.cpp)

# GLAD
set(GLAD_HOME vendors/glad)
add_library(glad ${GLAD_HOME}/src/glad/glad.c)
target_include_directories(glad PRIVATE ${GLAD_HOME}/include)
target_include_directories(Snake PRIVATE ${GLAD_HOME}/include)

target_link_libraries(Snake PUBLIC OpenGL::GL glfw glad glm)
