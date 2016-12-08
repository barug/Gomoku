// GomokuReferee.cpp for Gomoku in /home/josselin/rendu/tek3/IA/Gomoku/srcs
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Mon Dec  5 13:50:04 2016 Josselin
// Last update Tue Dec  6 16:07:36 2016 Josselin
//

#include <iostream>
#include "GomokuReferee.hpp"

constexpr GomokuReferee::Direction GomokuReferee::directions[8];

GomokuReferee::GomokuReferee(Map &map) : _map(map)
{}

GomokuReferee::~GomokuReferee()
{}

IReferee::gameState	GomokuReferee::validatePlayerAction(const unsigned int CoordX,
							    const unsigned int CoordY)
{
  std::cout << CoordX << " " << CoordY << std::endl;
  return IReferee::gameState::ONGOING;
}

int			countAlignement(const Map &map, Map::Coordinates coordinates,
					int xInc, int yInc)
  {
    int			count = 0;

    while (coordinates.x + xInc >= 0 && coordinates.x + xInc <= 19 &&
	   coordinates.y + yInc >= 0 && coordinates.y + yInc <= 19 &&
	   // MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc) <= MAP_SIZE &&
	   map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
	   map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)))
      {
	xInc = xInc < 0 ? xInc - 1 : xInc > 0 ? xInc + 1 : 0;
	yInc = yInc < 0 ? yInc - 1 : yInc > 0 ? yInc + 1 : 0;
	count++;
      }
    return count;
  }

std::vector<int>	testAlignement(Map &map, Map::Coordinates coordinates)
{
  std::vector<int> vec;

  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH, map, coordinates, Map::WHITE));
  // vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH, map, coordinates));

  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::WEST, map, coordinates, Map::WHITE));
  // vec.push_back(testAlignementInDirection(GomokuReferee::Direction::EAST, map, coordinates));

  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH_EAST, map, coordinates, Map::WHITE));
  // vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH_WEST, map, coordinates));

  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH_EAST, map, coordinates, Map::WHITE));
  // vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH_WEST, map, coordinates));

  return vec;
}

int			testAlignementInDirection(GomokuReferee::Direction direction,
						  const Map &map,
						  Map::Coordinates coordinates,
						  Map::CaseState color)
{
  int index = map.convertToIndex(coordinates);
  int nextCaseIndex;
  int				count = 1;
  const std::bitset<Map::boardSize>	&bitset = map.getBitSet(color);

  if (!((coordinates.x == 18
	 && (direction == GomokuReferee::NORTH_EAST
	     || direction == GomokuReferee::SOUTH_EAST
	     || direction == GomokuReferee::EAST))
	|| (coordinates.x == 0
	    && (direction == GomokuReferee::NORTH_WEST
		|| direction == GomokuReferee::SOUTH_WEST
		|| direction == GomokuReferee::WEST))))
    {
      for (int i = 1; i <= 5; i++)
	{
	  nextCaseIndex = index + i * direction;
	  if (nextCaseIndex < 0
	      || nextCaseIndex > Map::boardSize
	      || bitset[nextCaseIndex] != true)
	    break;
	  count++;
	}
    }
  if (!((coordinates.x == 18
	 && (-direction == GomokuReferee::NORTH_EAST
	     || -direction == GomokuReferee::SOUTH_EAST
	     || -direction == GomokuReferee::EAST))
	|| (coordinates.x == 0
	    && (-direction == GomokuReferee::NORTH_WEST
		|| -direction == GomokuReferee::SOUTH_WEST
		|| -direction == GomokuReferee::WEST))))
    {
      for (int i = 1; i <= 5; i++)
	{
	  nextCaseIndex = index - i * direction;
	  if (nextCaseIndex < 0
	      || nextCaseIndex > Map::boardSize
	      || bitset[nextCaseIndex] != true)
	    break; 
	  count++;
	}
    }
  return count;
}

bool				countCapture(const Map &map,
					     Map::Coordinates coordinates,
					     int xInc,
					     int yInc)
{
  Map::CaseState rivals = map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) == Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;

  if (map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)) == rivals &&
      map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2))) == rivals &&
      map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))) == map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x))
    return true;
  return false;
}
bool				testCaptureInDirection(GomokuReferee::Direction direction,
						       const Map &map,
						       Map::Coordinates coordinates)
{
  int xInc = 0;
  int yInc = 0;
  switch (direction)
    {
    case GomokuReferee::Direction::NORTH :
      xInc = 0;
      yInc = 1;
      break;

    case GomokuReferee::Direction::SOUTH :
      xInc = 0;
      yInc = -1;
      break;

    case GomokuReferee::Direction::WEST :
      xInc = -1;
      yInc = 0;
      break;

    case GomokuReferee::Direction::EAST :
      xInc = 1;
      yInc = 0;
      break;

    case GomokuReferee::Direction::NORTH_EAST :
      xInc = 1;
      yInc = 1;
      break;

    case GomokuReferee::Direction::SOUTH_EAST :
      xInc = 1;
      yInc = -1;
      break;

    case GomokuReferee::Direction::NORTH_WEST :
      xInc = -1;
      yInc = 1;
      break;

    case GomokuReferee::Direction::SOUTH_WEST :
      xInc = -1;
      yInc = -1;
      break;

    default :
      xInc = 0;
      yInc = 0;
    }
  if (coordinates.x + (xInc * 3) >= 0 && coordinates.x + (xInc * 3) <= 19 &&
      coordinates.y + (yInc * 3) >= 0 && coordinates.y + (yInc * 3) <= 19)
    //MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3)) > MAP_SIZE)
    return countCapture(map, coordinates, xInc, yInc);
  return false;
}

std::vector<GomokuReferee::Direction>	testCapture(Map &map, Map::Coordinates coordinates)
{
  std::vector<GomokuReferee::Direction> captureDirection;

  if (testCaptureInDirection(GomokuReferee::Direction::NORTH, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::NORTH);
  if (testCaptureInDirection(GomokuReferee::Direction::NORTH_EAST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::NORTH_EAST);
  if (testCaptureInDirection(GomokuReferee::Direction::EAST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::EAST);
  if (testCaptureInDirection(GomokuReferee::Direction::SOUTH_EAST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::SOUTH_EAST);
  if (testCaptureInDirection(GomokuReferee::Direction::SOUTH, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::SOUTH);
  if (testCaptureInDirection(GomokuReferee::Direction::SOUTH_WEST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::SOUTH_WEST);
  if (testCaptureInDirection(GomokuReferee::Direction::WEST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::WEST);
  if (testCaptureInDirection(GomokuReferee::Direction::NORTH_WEST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::NORTH_WEST);
  return captureDirection;
}
