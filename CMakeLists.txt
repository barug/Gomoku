#  _____ _____ _____ _____ _____ _____ 
# |   __|     |     |     |  |  |  |  |
# |  |  |  |  | | | |  |  |    -|  |  |
# |_____|_____|_|_|_|_____|__|__|_____|
#

cmake_minimum_required(VERSION 3.5)

project(Gomoku)

add_executable(Gomoku
  srcs/Case.cpp
  srcs/Gomoku.cpp
  srcs/Main.cpp
  srcs/TextureManager.cpp
  srcs/mSFML_Audio.cpp
  srcs/mSFML_Window.cpp
  srcs/map.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
set(LINK_LIBRARIES
  -lsfml-graphics
  -lsfml-window
  -lsfml-system
  -lsfml-audio)

message("Libraries linked -- > " ${LINK_LIBRARIES})
include_directories(./includes)
target_link_libraries(Gomoku ${LINK_LIBRARIES})
