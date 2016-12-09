// GomokuReferee.cpp for Gomoku in /home/josselin/rendu/tek3/IA/Gomoku/srcs
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Mon Dec  5 13:50:04 2016 Josselin
// Last update Fri Dec  9 22:19:29 2016 Josselin
//

#include <iostream>
#include "GomokuReferee.hpp"

constexpr GomokuReferee::Direction GomokuReferee::directions[8];

GomokuReferee::GomokuReferee(Map &map) : _map(map), _whiteCapturedPieces(0), _blackCapturedPieces(0)
{}

GomokuReferee::~GomokuReferee()
{}

// bool			GomokuReferee::testDoubleThree(Map::Coordinates coordinates)
// {
//   std::cout << "Test Double Three begin" << std::endl;
//   std::cout << coordinates.x << " " << coordinates.y << std::endl;
//   std::vector<int> v = testAlignement(_map, coordinates);
//   for (auto it : v)
//     std::cout << "v=" << it << std::endl;
//   std::cout << "Test Double Three end" << std::endl;
//   return false;
// }

/*
** Check player action
*/
IReferee::gameState	GomokuReferee::validatePlayerAction(int CoordX, int CoordY, const bool turn)
{


  // if (testDoubleThree(Map::Coordinates(CoordX, CoordY)) == true)
  //   return IReferee::gameState::UNVALID;


  if (turn) {
    std::cerr << "[WHITE TURN]" << std::endl;//////////////////////////////////////////////debug
    this->_map.setCaseAtIndex(MAP_WIDTH * CoordY + CoordX, Map::CaseState::WHITE);
  } else {
    std::cerr << "[BLACK TURN]" << std::endl;//////////////////////////////////////////////debug
    this->_map.setCaseAtIndex(MAP_WIDTH * CoordY + CoordX, Map::CaseState::BLACK);
  }

  std::cerr << "[REFEREE DEBUG]Validate player action" << std::endl;//////////////////////////////////////////////debug
  std::cout << "[REFEREE DEBUG]Position : " << CoordX << " " << CoordY << std::endl;//////////////////////////////////////////////debug

  testCapture(Map::Coordinates(CoordX, CoordY));
  std::cerr << "[REFEREE DEBUG]Test Capture OK" << std::endl;//////////////////////////////////////////////debug
  if (this->_whiteCapturedPieces >= 10)
    return IReferee::gameState::P1_WIN;
  else if (this->_blackCapturedPieces >= 10)
    return IReferee::gameState::P2_WIN;

  std::vector<int> vec = testAlignement(Map::Coordinates(CoordX, CoordY));
  for (unsigned int i = 0; i < vec.size(); i++)
    if (vec[i] >= 5)
      {
	std::cerr << "[REFEREE DEBUG]Test five in a row" << std::endl;//////////////////////////////////////////////debug
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

	if (hasFiveInARow(invertDirection(direction), Map::Coordinates(CoordX, CoordY)))
	  {
	    std::cerr << "[REFEREE DEBUG]Five in a row ok, game over" << std::endl;//////////////////////////////////////////////debug
	    if (turn)
	      return IReferee::gameState::P1_WIN;
	    else
	      return IReferee::gameState::P2_WIN;
	  }
	else
	  std::cerr << "[REFEREE DEBUG]Five in a row can be break" << std::endl;//////////////////////////////////////////////debug
      }
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
bool			GomokuReferee::simulateCapture(Map::Coordinates coordinates, Map::CaseState rivals,
						       int xInc, int yInc, int xIncBack, int yIncBack, int i)
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
		    this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + yBack) + (xPos + xBack)) == Map::CaseState::EMPTY &&
		    this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + y) + (xPos + x)) == this->_map.getCaseAtIndex(MAP_WIDTH * yPos + xPos) &&
		    this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + y * 2) + (xPos + x * 2)) == rivals)
		return true;
	    }
	}
    }
  return false;
}

bool			GomokuReferee::hasFiveInARow(GomokuReferee::Direction direction, Map::Coordinates coordinates)
{
  Map::CaseState	rivals = this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
				Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;
  int			xInc;
  int			yInc;
  int			xIncBack;
  int			yIncBack;
  int			i = 0;

  initIncDirection(direction, xInc, yInc);
  xIncBack = xInc == 0 ? 0 : xInc == -1 ? 1 : xInc == 1 ? -1 : 0;
  yIncBack = yInc == 0 ? 0 : yInc == -1 ? 1 : yInc == 1 ? -1 : 0;

  while (i < 5)
    if (simulateCapture(coordinates, rivals, xInc, yInc, xIncBack, yIncBack, i++))
      return false;
  return true;
}


/*
** Alignement Tests
*/
int			GomokuReferee::countAlignement(Map::Coordinates coordinates,
						       int xInc, int yInc)
  {
    int			count = 0;

    while (coordinates.x + xInc >= 0 && coordinates.x + xInc <= 19 &&
	   coordinates.y + yInc >= 0 && coordinates.y + yInc <= 19 &&
	   this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
	   this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)))
      {
	xInc = xInc < 0 ? xInc - 1 : xInc > 0 ? xInc + 1 : 0;
	yInc = yInc < 0 ? yInc - 1 : yInc > 0 ? yInc + 1 : 0;
	count++;
      }
    return count;
  }

int				GomokuReferee::testAlignementInDirection(GomokuReferee::Direction direction, Map::Coordinates coordinates)
{
  int				count;

  if (direction == GomokuReferee::Direction::NORTH)
    count = countAlignement(coordinates, 0, 1) + countAlignement(coordinates, 0, -1);
  else if (direction == GomokuReferee::Direction::WEST)
    count = countAlignement(coordinates, 1, 0) + countAlignement(coordinates, -1, 0);
  else if (direction == GomokuReferee::Direction::NORTH_EAST)
    count = countAlignement(coordinates, 1, 1) + countAlignement(coordinates, -1, -1);
  else
    count = countAlignement(coordinates, 1, -1) + countAlignement(coordinates, -1, 1);
  return count + 1;
}

std::vector<int>	GomokuReferee::testAlignement(Map::Coordinates coordinates)
{
  std::vector<int> vec;

  std::cerr << "[REFEREE DEBUG]Start alignement test" << std::endl;//////////////////////////////////////////////debug
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH, coordinates));
  std::cerr << "[REFEREE DEBUG]NORTH/SOUTH alignement : " << vec[0]  << std::endl;//////////////////////////////////////////////debug
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::WEST, coordinates));
  std::cerr << "[REFEREE DEBUG]WEST/EAST alignement : " << vec[1]  << std::endl;//////////////////////////////////////////////debug
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH_EAST, coordinates));
  std::cerr << "[REFEREE DEBUG]NORTH_EAST/SOUTH_WEST alignement : " << vec[2]  << std::endl;//////////////////////////////////////////////debug
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH_EAST, coordinates));
  std::cerr << "[REFEREE DEBUG]SOUTH_EAST/NORTH_WEST alignement : " << vec[3]  << std::endl;//////////////////////////////////////////////debug
  return vec;
}

/*
** Capture Tests
*/
void				GomokuReferee::capturePieces(Map::Coordinates coordinates, int xInc, int yInc)
{
  Map::CaseState rivals = this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
			Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;

  this->_map.setCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc), Map::CaseState::EMPTY);
  this->_map.setCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2)), Map::CaseState::EMPTY);

  std::cerr << "[REFEREE DEBUG]Capture !" << std::endl;//////////////////////////////////////////////debug
  if (rivals == Map::CaseState::WHITE)
    this->_blackCapturedPieces += 2;
  else
    this->_whiteCapturedPieces += 2;
}

bool				GomokuReferee::hasCapture(Map::Coordinates coordinates, int xInc, int yInc)
{
  Map::CaseState rivals = this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
    Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;

  if (this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)) == rivals &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2))) == rivals &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))) == this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x))
    return true;
  return false;
}

void				GomokuReferee::testCaptureInDirection(GomokuReferee::Direction direction, Map::Coordinates coordinates)
{
  int xInc = 0;
  int yInc = 0;

  initIncDirection(direction, xInc, yInc);
  if (coordinates.x + (xInc * 3) >= 0 && coordinates.x + (xInc * 3) <= 19 &&
      coordinates.y + (yInc * 3) >= 0 && coordinates.y + (yInc * 3) <= 19)
    if (hasCapture(coordinates, xInc, yInc))
      capturePieces(coordinates, xInc, yInc);
}

void				GomokuReferee::testCapture(Map::Coordinates coordinates)
{
  std::cerr << "[REFEREE DEBUG]Start capture test" << std::endl;//////////////////////////////////////////////debug
  testCaptureInDirection(GomokuReferee::Direction::NORTH, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::NORTH_EAST, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::EAST, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::SOUTH_EAST, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::SOUTH, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::SOUTH_WEST, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::WEST, coordinates);
  testCaptureInDirection(GomokuReferee::Direction::NORTH_WEST, coordinates);
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

int			testAlignementInDirection(GomokuReferee::Direction direction,
						  const Map &map,
						  Map::Coordinates coordinates,
						  Map::CaseState color)
{
  int			index = map.convertToIndex(coordinates);
  int			nextCaseIndex;
  int				count = 0;
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
