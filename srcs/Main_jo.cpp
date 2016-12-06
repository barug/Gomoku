//
// Main.cpp for Gomuko in /home/mikaz3/Tek3/B5/AI
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Oct 12 11:52:44 2016 Thomas Billot
// Last update Mon Dec  5 16:36:48 2016 Josselin
//

#include "GomokuReferee.hpp"
#include "Map.hpp"
#include <iostream>

int			main(void)
{
  // BoardGame		game;

  // return game.start();

  std::vector<char> mapData 
	  {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 1, 1, 2, 2, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Map map(mapData);

  std::cout << "alignement North "
	    << testAlignementInDirection(GomokuReferee::NORTH,
					 map,
					 Map::Coordinates(3, 11))
	    << std::endl;
  std::cout << "alignement North East: "
	    << testAlignementInDirection(GomokuReferee::NORTH_EAST,
					 map,
					 Map::Coordinates(3, 11))
	    << std::endl;
  std::cout << "alignement South East: "
	    << testAlignementInDirection(GomokuReferee::SOUTH_EAST,
					 map,
					 Map::Coordinates(3, 11))
	    << std::endl;
    std::cout << "alignement West: "
	    << testAlignementInDirection(GomokuReferee::WEST,
					 map,
					 Map::Coordinates(3, 11))
	    << std::endl;

  std::cout << "capture in North: " << testCaptureInDirection(GomokuReferee::NORTH,
							      map,
							      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture in North East: "
	    << testCaptureInDirection(GomokuReferee::NORTH_EAST,
				      map,
				      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture in East: "
	    << testCaptureInDirection(GomokuReferee::EAST,
				      map,
				      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture in South East: "
	    << testCaptureInDirection(GomokuReferee::SOUTH_EAST,
				      map,
				      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture in South: "
	    << testCaptureInDirection(GomokuReferee::SOUTH,
				      map,
				      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture in South West: "
	    << testCaptureInDirection(GomokuReferee::SOUTH_WEST,
				      map,
				      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture in West: "
	    << testCaptureInDirection(GomokuReferee::WEST,
				      map,
				      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture in North West: "
	    << testCaptureInDirection(GomokuReferee::NORTH_WEST,
				      map,
				      Map::Coordinates(8, 3))
	    << std::endl;
  std::cout << "capture Fail: "
	    << testCaptureInDirection(GomokuReferee::NORTH_WEST,
				      map,
				      Map::Coordinates(10, 10))
	    << std::endl;

  // map.setCaseAt(Map::Coordinates(9, 10), Map::CaseState::WHITE);
  // map.setCaseAt(Map::Coordinates(10, 10), Map::CaseState::BLACK);
  // map.setCaseAt(Map::Coordinates(11, 10), Map::CaseState::BLACK);
  // map.setCaseAt(Map::Coordinates(12, 10), Map::CaseState::WHITE);

  // map.setCaseAt(Map::Coordinates(12, 11), Map::CaseState::BLACK);
  // map.setCaseAt(Map::Coordinates(12, 12), Map::CaseState::BLACK);
  // map.setCaseAt(Map::Coordinates(12, 13), Map::CaseState::WHITE);

  // map.setCaseAt(Map::Coordinates(12, 9), Map::CaseState::BLACK);
  // map.setCaseAt(Map::Coordinates(12, 8), Map::CaseState::BLACK);
  // map.setCaseAt(Map::Coordinates(12, 7), Map::CaseState::WHITE);


  // // GomokuReferee gomoku(map);
  // // std::cout << testAlignement(GomokuReferee::Direction::NORTH, map, Map::Coordinates(10, 10)) << std::endl;
  // std::vector<GomokuReferee::Direction> vec;
  // vec = testCapture(map, Map::Coordinates(12, 10));
  // for (size_t i = 0; i < vec.size(); i++)
  //   std::cout << vec[i] << std::endl;
}
