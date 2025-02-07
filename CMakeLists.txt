cmake_minimum_required(VERSION 3.20)

# Project name
project(pong VERSION 1.0.0)

set(SDL2_INCLUDE_DIR "F:/SDL2-2.30.11/include")
set(SDL2_LIBRARY "F:/SDL2-2.30.11/lib/x64/SDL2.lib")
set(SDL2MAIN_LIBRARY "F:/SDL2-2.30.11/lib/x64/SDL2main.lib")

# Find all .cpp files automatically
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)


# Find OpenGL
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp "src/RenderWindow.cpp" "src/RenderWindow.h" "src/Ball.h" "src/Ball.cpp" "src/Paddle.h" "src/Paddle.cpp" "src/Score.h" "src/Score.cpp") 

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)


