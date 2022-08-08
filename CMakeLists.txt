cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Asteroid src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/spaceship.cpp src/spaceship.h src/spaceObject.cpp src/spaceObject.h src/asteroid.cpp src/asteroid.h src/missile.cpp src/missile.h src/mouse.cpp src/mouse.h)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Asteroid ${SDL2_LIBRARIES})
