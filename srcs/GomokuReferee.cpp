// GomokuReferee.cpp for Gomoku in /home/josselin/rendu/tek3/IA/Gomoku/srcs
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Mon Dec  5 13:50:04 2016 Josselin
// Last update Fri Dec  9 14:54:03 2016 Josselin
//

#include <iostream>
#include "GomokuReferee.hpp"

GomokuReferee::GomokuReferee(Map &map) : _map(map), _whiteCapturedPieces(0), _blackCapturedPieces(0)
{}

GomokuReferee::~GomokuReferee()
{}


/*
** Check player action
*/
IReferee::gameState	GomokuReferee::validatePlayerAction(int CoordX, int CoordY, const bool turn)
{
  //check regle double trois
	//-> return UNVALID


  std::cerr << "Validate player action" << std::endl;//////////////////////////////////////////////debug
  testCapture(this->_map, Map::Coordinates(CoordX, CoordY));
  std::cerr << "Test Capture OK" << std::endl;//////////////////////////////////////////////debug
  if (this->_whiteCapturedPieces >= 10)
    return IReferee::gameState::P1_WIN;
  else if (this->_blackCapturedPieces >= 10)
    return IReferee::gameState::P2_WIN;

  std::vector<int> vec = testAlignement(this->_map, Map::Coordinates(CoordX, CoordY));
  for (unsigned int i = 0; i < vec.size(); i++)
    {
      std::cerr << "alignement : " << vec[i] << std::endl;//////////////////////////////////////////////debug
      if (vec[i] >= 5)
	{
	  std::cerr << "test five in a row" << std::endl;//////////////////////////////////////////////debug
	  GomokuReferee::Direction direction;
	  direction =
	    i == 0 ? GomokuReferee::Direction::NORTH :
	    i == 1 ? GomokuReferee::Direction::WEST :
	    i == 2 ? GomokuReferee::Direction::NORTH_EAST :
	    GomokuReferee::Direction::SOUTH_EAST;

	  int xInc;
	  int yInc;
	  initIncDirection(direction, xInc, yInc);

	  while (CoordX + xInc >= 0 && CoordX + xInc <= 19 &&
		 CoordY + yInc >= 0 && CoordY + yInc <= 19 &&
		 this->_map.getCaseAtIndex(MAP_WIDTH * CoordY + CoordX) ==
		 this->_map.getCaseAtIndex(MAP_WIDTH * (CoordY + yInc) + (CoordX + xInc)))
	    {
	      CoordX += xInc;
	      CoordY += yInc;
	    }

	  if (hasFiveInARow(invertDirection(direction), this->_map, Map::Coordinates(CoordX, CoordY)))
	    {
	      std::cerr << "five in a row ok, game over" << std::endl;//////////////////////////////////////////////debug
	      if (turn)
		return IReferee::gameState::P2_WIN;
	      else
		return IReferee::gameState::P1_WIN;
	    }
	}
    }
  std::cout << CoordX << " " << CoordY << std::endl;
  return IReferee::gameState::ONGOING;
}


/*
** Get Direction
*/
GomokuReferee::Direction	GomokuReferee::invertDirection(GomokuReferee::Direction direction)
{
  direction =
    direction == GomokuReferee::Direction::NORTH ? GomokuReferee::Direction::SOUTH :
    direction == GomokuReferee::Direction::WEST ? GomokuReferee::Direction::EAST :
    direction == GomokuReferee::Direction::NORTH_EAST ? GomokuReferee::Direction::SOUTH_WEST :
    GomokuReferee::Direction::NORTH_WEST;

  return direction;
}

void		GomokuReferee::initIncDirection(GomokuReferee::Direction direction, int &xInc, int &yInc)
{
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
      break;
    }
}


/*
** Game Over Tests / Cinq Cassable
*/
bool			GomokuReferee::simulateCapture(Map &map, Map::Coordinates coordinates,
					Map::CaseState rivals,
					int xInc, int yInc, int xIncBack,
					int yIncBack, int i)
{
  int xPos = coordinates.x + (xInc * i);
  int yPos = coordinates.y + (yInc * i);
  for (int x = -1; x < 2; x++)
    {
      for (int y = -1; y < 2; y++)
	{
	  if ((x == xInc && y == yInc) || (x == xIncBack && y == yIncBack));
	  else
	    {
		int xBack = x == 0 ? 0 : x == -1 ? 1 : x == 1 ? -1 : 0;
		int yBack = y == 0 ? 0 : y == -1 ? 1 : y == 1 ? -1 : 0;

		if ((yPos + yBack >= 0 && yPos + yBack <= 19) &&
		    (xPos + xBack >= 0 && xPos + xBack <= 19) &&
		    (yPos + y * 2 >= 0 && yPos + y * 2 <= 19) &&
		    (xPos + x * 2 >= 0 && xPos + x * 2 <= 19) &&
		    map.getCaseAtIndex(MAP_WIDTH * (yPos + yBack) + (xPos + xBack)) == Map::CaseState::EMPTY &&
		    map.getCaseAtIndex(MAP_WIDTH * (yPos + y) + (xPos + x)) == map.getCaseAtIndex(MAP_WIDTH * yPos + xPos) &&
		    map.getCaseAtIndex(MAP_WIDTH * (yPos + y * 2) + (xPos + x * 2)) == rivals)
		return true;
	    }
	}
    }
  return false;
}

bool			GomokuReferee::hasFiveInARow(GomokuReferee::Direction direction,
					   Map &map,
					   Map::Coordinates coordinates)
{
  Map::CaseState	rivals = map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
				Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;
  int			xInc;
  int			xIncBack;
  int			yInc;
  int			yIncBack;
  int			i = 0;

  initIncDirection(direction, xInc, yInc);
  xIncBack = xInc == 0 ? 0 : xInc == -1 ? 1 : xInc == 1 ? -1 : 0;
  yIncBack = yInc == 0 ? 0 : yInc == -1 ? 1 : yInc == 1 ? -1 : 0;

  while (i < 5)
    if (simulateCapture(map, coordinates, rivals, xInc, yInc, xIncBack, yIncBack, i++))
      return false;
  return true;
}


/*
** Alignement Tests
*/
int			GomokuReferee::countAlignement(const Map &map, Map::Coordinates coordinates,
					int xInc, int yInc)
  {
    int			count = 0;

    while (coordinates.x + xInc >= 0 && coordinates.x + xInc <= 19 &&
	   coordinates.y + yInc >= 0 && coordinates.y + yInc <= 19 &&
	   map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
	   map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)))
      {
	xInc = xInc < 0 ? xInc - 1 : xInc > 0 ? xInc + 1 : 0;
	yInc = yInc < 0 ? yInc - 1 : yInc > 0 ? yInc + 1 : 0;
	count++;
      }
    return count;
  }

int				GomokuReferee::testAlignementInDirection(GomokuReferee::Direction direction, const Map &map, Map::Coordinates coordinates)
{
  int				count;

  std::cerr << "test alignement in direction " << direction << std::endl;//////////////////////////////////////////////debug
  if (direction == GomokuReferee::Direction::NORTH)
    count = countAlignement(map, coordinates, 0, 1) + countAlignement(map, coordinates, 0, -1);
  else if (direction == GomokuReferee::Direction::WEST)
    count = countAlignement(map, coordinates, 1, 0) + countAlignement(map, coordinates, -1, 0);
  else if (direction == GomokuReferee::Direction::NORTH_EAST)
    count = countAlignement(map, coordinates, 1, 1) + countAlignement(map, coordinates, -1, -1);
  else
    count = countAlignement(map, coordinates, 1, -1) + countAlignement(map, coordinates, -1, 1);
  return count + 1;
}

std::vector<int>	GomokuReferee::testAlignement(const Map &map, Map::Coordinates coordinates)
{
  std::vector<int> vec;

  std::cerr << "start alignement test" << std::endl;//////////////////////////////////////////////debug
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH, map, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::WEST, map, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH_EAST, map, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH_EAST, map, coordinates));
  return vec;
}


/*
** Capture Tests
*/
void				GomokuReferee::capturePieces(Map &map, Map::Coordinates coordinates, int xInc, int yInc)
{
  Map::CaseState rivals = map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) == Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;

  map.setCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc), Map::CaseState::EMPTY);
  map.setCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2)), Map::CaseState::EMPTY);

  std::cerr << "Capture !" << std::endl;//////////////////////////////////////////////debug
  if (rivals == Map::CaseState::WHITE)
    this->_blackCapturedPieces += 2;
  else
    this->_whiteCapturedPieces += 2;
}

bool				GomokuReferee::hasCapture(Map &map, Map::Coordinates coordinates, int xInc, int yInc)
{
  Map::CaseState rivals = map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) == Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;

  if (map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)) == rivals &&
      map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2))) == rivals &&
      map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))) == map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x))
    return true;
  return false;
}

void				GomokuReferee::testCaptureInDirection(GomokuReferee::Direction direction,
						       Map &map,
						       Map::Coordinates coordinates)
{
  int xInc = 0;
  int yInc = 0;

  std::cerr << "test capture in direction " << direction << std::endl;//////////////////////////////////////////////debug
  initIncDirection(direction, xInc, yInc);
  if (coordinates.x + (xInc * 3) >= 0 && coordinates.x + (xInc * 3) <= 19 &&
      coordinates.y + (yInc * 3) >= 0 && coordinates.y + (yInc * 3) <= 19)
    if (hasCapture(map, coordinates, xInc, yInc))
      capturePieces(map, coordinates, xInc, yInc);
}

void				GomokuReferee::testCapture(Map &map, Map::Coordinates coordinates)
{
  std::cerr << "start capture test" << std::endl;//////////////////////////////////////////////debug
  testCaptureInDirection(GomokuReferee::Direction::NORTH, map, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::NORTH_EAST, map, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::EAST, map, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::SOUTH_EAST, map, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::SOUTH, map, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::SOUTH_WEST, map, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::WEST, map, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::NORTH_WEST, map, coordinates);
}


/*
** Set & Get
*/

int			GomokuReferee::getWhiteCapturedPieces()
{
  return this->_whiteCapturedPieces;
}

int			GomokuReferee::getBlackCapturedPieces()
{
  return this->_blackCapturedPieces;
}
