#  _____ _____ _____ _____ _____ _____
# |   __|     |     |     |  |  |  |  |
# |  |  |  |  | | | |  |  |    -|  |  |
# |_____|_____|_|_|_|_____|__|__|_____|
#

cmake_minimum_required(VERSION 3.5)

project(Gomoku)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# if(WIN32)
#   link_directories(${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/win32)
# else()
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/linux)
# endif()

 link_libraries(-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)

add_executable(Gomoku
  srcs/Game.cpp
  srcs/Player.cpp
  srcs/Main.cpp
  srcs/Timer.cpp
  srcs/GomokuUI.cpp
  srcs/GomokuReferee.cpp
  srcs/TextureManager.cpp
  srcs/mSFML_Audio.cpp
  srcs/mSFML_Window.cpp
  srcs/Map.cpp
  srcs/Coordinates.cpp
  )

target_link_libraries(Gomoku sfml-window sfml-system sfml-audio sfml-graphics)
