##
## Made by kama
## email   thomas.bogard@epitech.eu
##

cmake_minimum_required(VERSION 3.5)
project(msfml)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(msfml main.cpp mSFML_Audio.cpp mSFML_Window.cpp TextureManager.cpp)
target_link_libraries(msfml sfml-window sfml-system sfml-audio sfml-graphics)
