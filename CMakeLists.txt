cmake_minimum_required(VERSION 3.15)
project(Helicopter)

set(CMAKE_CXX_STANDARD 14)

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Helicopter main.cpp Bat.cpp Gameplay.cpp Obstacle.cpp Misc.cpp Grass.cpp Grass.h)
target_link_libraries(Helicopter sfml-graphics sfml-audio)