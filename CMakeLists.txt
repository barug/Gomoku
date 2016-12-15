#  _____ _____ _____ _____ _____ _____
# |   __|     |     |     |  |  |  |  |
# |  |  |  |  | | | |  |  |    -|  |  |
# |_____|_____|_|_|_|_____|__|__|_____|
#

cmake_minimum_required(VERSION 3.5)
project(Gomoku)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mSFML)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Gomoku
  srcs/Game.cpp
  srcs/Player.cpp
  srcs/Main.cpp
  srcs/Timer.cpp
  srcs/GomokuUI.cpp
  srcs/GomokuReferee.cpp
  srcs/Map.cpp
  srcs/Coordinates.cpp
  srcs/MinMax.cpp
  srcs/ArtificialPlayer.cpp
  srcs/HumanPlayer.cpp
  mSFML/mSFML_Audio.cpp
  mSFML/mSFML_Window.cpp
  mSFML/TextureManager.cpp)

target_link_libraries(Gomoku sfml-window sfml-system sfml-audio sfml-graphics)
