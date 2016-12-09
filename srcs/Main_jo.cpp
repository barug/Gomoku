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
#include "MinMax.hpp"
#include "Map.hpp"
#include <iostream>


void			testCaptureAndAlignement(const Map &map,
						 Map::Coordinates c,
						 Map::CaseState color)
{
  std::cout << "test for position x: " << c.x << " y: " << c.y << std::endl;
  std::cout << "alignement North "
	    << testAlignementInDirection(GomokuReferee::NORTH,
					 map,
					 c,
					 color)
	    << std::endl;
  std::cout << "alignement North East: "
	    << testAlignementInDirection(GomokuReferee::NORTH_EAST,
					 map,
					 c,
					 color)
	    << std::endl;
  std::cout << "alignement South East: "
	    << testAlignementInDirection(GomokuReferee::SOUTH_EAST,
					 map,
					 c,
					 color)
	    << std::endl;
  std::cout << "alignement West: "
	    << testAlignementInDirection(GomokuReferee::WEST,
					 map,
					 c,
					 color)
	    << std::endl;
  
  std::cout << "capture in North: " << testCaptureInDirection(GomokuReferee::NORTH,
							      map,
							      c)
	    << std::endl;
  std::cout << "capture in North East: "
	    << testCaptureInDirection(GomokuReferee::NORTH_EAST,
				      map,
				      c)
	    << std::endl;
  std::cout << "capture in East: "
	    << testCaptureInDirection(GomokuReferee::EAST,
				      map,
				      c)
	    << std::endl;
  std::cout << "capture in South East: "
	    << testCaptureInDirection(GomokuReferee::SOUTH_EAST,
				      map,
				      c)
	    << std::endl;
  std::cout << "capture in South: "
	    << testCaptureInDirection(GomokuReferee::SOUTH,
				      map,
				      c)
	    << std::endl;
  std::cout << "capture in South West: "
	    << testCaptureInDirection(GomokuReferee::SOUTH_WEST,
				      map,
				      c)
	    << std::endl;
  std::cout << "capture in West: "
	    << testCaptureInDirection(GomokuReferee::WEST,
				      map,
				      c)
	    << std::endl;
  std::cout << "capture in North West: "
	    << testCaptureInDirection(GomokuReferee::NORTH_WEST,
				      map,
				      c)
	    << std::endl;
  std::cout << "----------------------" << std::endl;
}

int			main(void)
{
  // BoardGame		game;

  // return game.start();
  GomokuMinMax		minMax;
  // std::vector<char>	mapData 
  // 	  {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 1, 1, 2, 2, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
  // 	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
  // 	   0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0,
  // 	   0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0,
  // 	   0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0,
  // 	   0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // 	   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
    std::vector<char>	mapData 
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
    Map map(mapData);
    
  // testCaptureAndAlignement(map, Map::Coordinates(3, 11), Map::WHITE);
  // testCaptureAndAlignement(map, Map::Coordinates(8, 3), Map::WHITE);
  // testCaptureAndAlignement(map, Map::Coordinates(12, 11), Map::BLACK);
  // testCaptureAndAlignement(map, Map::Coordinates(18, 6), Map::WHITE);
  // testCaptureAndAlignement(map, Map::Coordinates(0, 6), Map::WHITE);
  // testCaptureAndAlignement(map, Map::Coordinates(18, 7), Map::WHITE);
  // testCaptureAndAlignement(map, Map::Coordinates(10, 18), Map::WHITE);
  // testCaptureAndAlignement(map, Map::Coordinates(3, 18), Map::WHITE);

  // std::cout << "capture Fail: "
  // 	    << testCaptureInDirection(GomokuReferee::NORTH_WEST,
  // 				      map,
  // 				      Map::Coordinates(10, 10))
  // 	    << std::endl;

  // std::cout << "test aligment action Score calculation in 3 11: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(3, 11), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 0 0: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(0, 0), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 8 1: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(8, 3), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 12 11: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(12, 11), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 17 3: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(17, 3), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 3 18: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(3, 18), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 15 18: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(15, 18), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 15 15: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(15, 15), true)
  // 	    << std::endl;
  // std::cout << "test action Score calculation in 18 6: "
  // 	    << minMax.calculateActionScore(map, Map::Coordinates(18, 6), true)
  // 	    << std::endl;

  Map::Coordinates result = minMax.computeNextAction(map);
  std::cout << "min max result x: " << result.x << " y: "
  	    << result.y << std::endl;    
    
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
