// GomokuReferee.cpp for Gomoku in /home/josselin/rendu/tek3/IA/Gomoku/srcs
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Mon Dec  5 13:50:04 2016 Josselin
// Last update Sat Dec 10 17:50:47 2016 Josselin
//

#include <iostream>
#include "GomokuReferee.hpp"

constexpr GomokuReferee::Direction GomokuReferee::directions[8];

GomokuReferee::GomokuReferee(Map &map) : _map(map), _whiteCapturedPieces(0), _blackCapturedPieces(0)
{}

GomokuReferee::~GomokuReferee()
{}


/*
** Test Double Trois
*/
bool			checkPattern1(Map &map, Map::Coordinates coordinates, Map::Coordinates direction)
{
  int			i = 0;
  int			count = 0;
  int			countEmpty = 0;

  while (i < 3)
    {
      if (map.getCaseAt(coordinates) == 2)
	count++;
      else if (map.getCaseAt(coordinates) == 0)
	countEmpty++;
 //      std::cout << "Case Info =" << map.getCaseAt(coordinates) << "Testing in x=" << coordinates.x << "
 // y=" << coordinates.y << std::endl;
      coordinates = coordinates + direction;
      i++;
    }
  if (count == 3 && countEmpty == 0)
    return true;
  return false;
}

bool			checkPattern2(Map &map, Map::Coordinates coordinates, Map::Coordinates direction)
{
  int			i = 0;
  int			countPawn = 0;
  int			countEmpty = 0;

  while (i <= 3)
    {
      if (map.getCaseAt(coordinates) == 2)
	countPawn++;
      else if (map.getCaseAt(coordinates) == 0)
	countEmpty++;
      coordinates = coordinates + direction;
      i++;
    }
  if (countPawn == 3 && countEmpty == 1)
    return true;
  return false;
}

Map::Coordinates	Pattern1(Map &map, Map::Coordinates coordinates)
{
  if (checkPattern1(map, coordinates, Map::Coordinates(-1, -1)) == true)
    return (Map::Coordinates(-1, -1));
  if (checkPattern1(map, coordinates, Map::Coordinates(0, -1)) == true)
    return (Map::Coordinates(0, -1));
  if (checkPattern1(map, coordinates, Map::Coordinates(1, -1)) == true)
    return (Map::Coordinates(1, -1));
  if (checkPattern1(map, coordinates, Map::Coordinates(1, 0)) == true)
    return (Map::Coordinates(1, 0));
  if (checkPattern1(map, coordinates, Map::Coordinates(1, 1)) == true)
    return (Map::Coordinates(1, 1));
  if (checkPattern1(map, coordinates, Map::Coordinates(0, 1)) == true)
    return (Map::Coordinates(0, 1));
  if (checkPattern1(map, coordinates, Map::Coordinates(-1, 1)) == true)
    return (Map::Coordinates(-1, 1));
  if (checkPattern1(map, coordinates, Map::Coordinates(-1, 0)) == true)
    return (Map::Coordinates(-1, 0));
  return (coordinates);
}

Map::Coordinates	Pattern2(Map &map, Map::Coordinates coordinates)
{
  if (checkPattern2(map, coordinates, Map::Coordinates(-1, -1)) == true)
    return (Map::Coordinates(-1, -1));
  if (checkPattern2(map, coordinates, Map::Coordinates(0, -1)) == true)
    return (Map::Coordinates(0, -1));
  if (checkPattern2(map, coordinates, Map::Coordinates(1, -1)) == true)
    return (Map::Coordinates(1, -1));
  if (checkPattern2(map, coordinates, Map::Coordinates(1, 0)) == true)
    return (Map::Coordinates(1, 0));
  if (checkPattern2(map, coordinates, Map::Coordinates(1, 1)) == true)
    return (Map::Coordinates(1, 1));
  if (checkPattern2(map, coordinates, Map::Coordinates(0, 1)) == true)
    return (Map::Coordinates(0, 1));
  if (checkPattern2(map, coordinates, Map::Coordinates(-1, 1)) == true)
    return (Map::Coordinates(-1, 1));
  if (checkPattern2(map, coordinates, Map::Coordinates(-1, 0)) == true)
    return (Map::Coordinates(-1, 0));
  return (coordinates);
}

bool			GomokuReferee::testDoubleThree(Map::Coordinates coordinates)
{
  std::cout << "Test Double Three begin" << std::endl;
  Map::Coordinates	c(Pattern1(_map, coordinates));
  std::cout << "RETURN VALUE OF PATTERN1=" << c.x << " " << c.y << std::endl;
  if (c.x != coordinates.x || c.y != coordinates.y)
    std::cout << "FOUND P1=" << c.x << " " << c.y << std::endl;
  Map::Coordinates	cPlus1(coordinates + Map::Coordinates(0, 1));
  std::cout << "CPLUS1=" << cPlus1.x << " " << cPlus1.y << std::endl;
  Map::Coordinates	c2(Pattern1(_map, cPlus1));
  std::cout << "RETURN VALUE OF PATTERN1=" << c2.x << " " << c2.y << std::endl;
  if (c2.x != cPlus1.x || c2.y != cPlus1.y)
    std::cout << "FOUND P1=" << c2.x << " " << c2.y << std::endl;
  Map::Coordinates	c1(Pattern2(_map, coordinates));
  std::cout << "RETURN VALUE OF PATTERN2=" << c1.x << " " << c1.y << std::endl;
  if (c1.x != coordinates.x || c1.y != coordinates.y)
    std::cout << "FOUND P2=" << c1.x << " " << c1.y << std::endl;
  std::cout << "Test Double Three end" << std::endl;
  return false;
}


/*
** Check player action
*/
void debug(Map &map, int CoordX, int CoordY)
{
  //////////////////////////////////////////////debug
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 19; j++) {
      std::cout << map.getCaseAtIndex(MAP_WIDTH * i + j) << " ";
    }
    std::cout << std::endl;
  }
  std::cerr << "[REFEREE DEBUG]Validate player action" << std::endl;//////////////////////////////////////////////debug
  std::cerr << "[REFEREE DEBUG]Position : " << CoordX << " " << CoordY << std::endl;//////////////////////////////////////////////debug
  //////////////////////////////////////////////debug
}

IReferee::GameState	GomokuReferee::validatePlayerAction(int CoordX, int CoordY, const bool turn)
{

  setTurn(CoordX, CoordY, turn);

  if (testDoubleThree(Map::Coordinates(CoordX, CoordY)))
    {
      this->_map.setCaseAt(Map::Coordinates((CoordX), (CoordY)), Map::CaseState::EMPTY);
      return IReferee::GameState::UNVALID;
    }

  debug(this->_map, CoordX, CoordY);//////////////////////////////////////////////debug

  testCapture(Map::Coordinates(CoordX, CoordY));
  if (this->_whiteCapturedPieces >= 10)
    return IReferee::GameState::P1_WIN;
  else if (this->_blackCapturedPieces >= 10)
    return IReferee::GameState::P2_WIN;
  std::cerr << "[REFEREE DEBUG]End Test Capture" << std::endl;//////////////////////////////////////////////debug

  std::vector<int> vec = testAlignement(Map::Coordinates(CoordX, CoordY));
  for (unsigned int i = 0; i < vec.size(); i++)
    if (vec[i] >= 5)
      return TestFiveInARow(CoordX, CoordY, i, turn);
  return IReferee::GameState::ONGOING;
}

void			GomokuReferee::setTurn(int CoordX, int CoordY, const bool turn)
{
  if (turn)
    {
      std::cerr << "[BLACK TURN]" << std::endl;//////////////////////////////////////////////debug
      this->_map.setCaseAtIndex(MAP_WIDTH * CoordY + CoordX, Map::CaseState::BLACK);
    }
  else
    {
      std::cerr << "[WHITE TURN]" << std::endl;//////////////////////////////////////////////debug
      this->_map.setCaseAtIndex(MAP_WIDTH * CoordY + CoordX, Map::CaseState::WHITE);
    }
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
		  ((this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + yBack) + (xPos + xBack)) == Map::CaseState::EMPTY &&
		    this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + y) + (xPos + x)) == this->_map.getCaseAtIndex(MAP_WIDTH * yPos + xPos) &&
		    this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + y * 2) + (xPos + x * 2)) == rivals) ||
		   (this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + yBack) + (xPos + xBack)) == rivals &&
		    this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + y) + (xPos + x)) == this->_map.getCaseAtIndex(MAP_WIDTH * yPos + xPos) &&
		    this->_map.getCaseAtIndex(MAP_WIDTH * (yPos + y * 2) + (xPos + x * 2)) == Map::CaseState::EMPTY)))
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

IReferee::GameState		GomokuReferee::TestFiveInARow(int CoordX, int CoordY, int i, const bool turn)
{
  std::cerr << "[REFEREE DEBUG]Test five in a row" << std::endl;//////////////////////////////////////////////debug
  GomokuReferee::Direction	direction;
  int				xInc;
  int				yInc;

  direction =
    i == 0 ? GomokuReferee::Direction::NORTH :
    i == 1 ? GomokuReferee::Direction::WEST :
    i == 2 ? GomokuReferee::Direction::NORTH_EAST :
    GomokuReferee::Direction::SOUTH_EAST;

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
	return IReferee::GameState::P2_WIN;
      else
	return IReferee::GameState::P1_WIN;
    }
  std::cerr << "[REFEREE DEBUG]Five in a row can be break" << std::endl;//////////////////////////////////////////////debug
  return IReferee::GameState::ONGOING;
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

  this->_map.setCaseAt(Map::Coordinates((coordinates.x + xInc), (coordinates.y + yInc)), Map::CaseState::EMPTY);
  this->_map.setCaseAt(Map::Coordinates((coordinates.x + (xInc * 2)), (coordinates.y + (yInc * 2))), Map::CaseState::EMPTY);

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
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))) ==
      this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x))
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
int			GomokuReferee::getP1Score()
{
  return this->_whiteCapturedPieces;
}

int			GomokuReferee::getP2Score()
{
  return this->_blackCapturedPieces;
}


/*
** IA Tests
*/
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
