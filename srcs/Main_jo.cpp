//
// Main.cpp for Gomuko in /home/mikaz3/Tek3/B5/AI
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Oct 12 11:52:44 2016 Thomas Billot
// Last update Mon Dec  5 16:36:48 2016 Josselin
//

# include		"BoardGame.hpp"
# include "GomokuReferee.hpp"
#include "Map.hpp"
#include <iostream>

int			main(void)
{
  // BoardGame		game;

  // return game.start();

  Map map;
  map.setCaseAt(Map::Coordinates(9, 10), Map::CaseState::WHITE);
  map.setCaseAt(Map::Coordinates(10, 10), Map::CaseState::BLACK);
  map.setCaseAt(Map::Coordinates(11, 10), Map::CaseState::BLACK);
  map.setCaseAt(Map::Coordinates(12, 10), Map::CaseState::WHITE);

  map.setCaseAt(Map::Coordinates(12, 11), Map::CaseState::BLACK);
  map.setCaseAt(Map::Coordinates(12, 12), Map::CaseState::BLACK);
  map.setCaseAt(Map::Coordinates(12, 13), Map::CaseState::WHITE);

  map.setCaseAt(Map::Coordinates(12, 9), Map::CaseState::BLACK);
  map.setCaseAt(Map::Coordinates(12, 8), Map::CaseState::BLACK);
  map.setCaseAt(Map::Coordinates(12, 7), Map::CaseState::WHITE);


  // GomokuReferee gomoku(map);
  // std::cout << testAlignement(GomokuReferee::Direction::NORTH, map, Map::Coordinates(10, 10)) << std::endl;
  std::vector<GomokuReferee::Direction> vec;
  vec = testCapture(map, Map::Coordinates(12, 10));
  for (size_t i = 0; i < vec.size(); i++)
    std::cout << vec[i] << std::endl;
}
