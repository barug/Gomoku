// GomokuReferee.cpp for Gomoku in /home/josselin/rendu/tek3/IA/Gomoku/srcs
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Mon Dec  5 13:50:04 2016 Josselin
// Last update Thu Dec 15 22:39:49 2016 Thomas Billot
//

#include <iostream>
#include <cmath>
#include "GomokuReferee.hpp"

constexpr GomokuReferee::Direction GomokuReferee::directions[8];

const Map::Coordinates GomokuReferee::DirectionsHelper::_directions[8] =
  {{Map::Coordinates(1, 0)},
   {Map::Coordinates(-1, 0)},
   {Map::Coordinates(0, 1)},
   {Map::Coordinates(0, -1)},
   {Map::Coordinates(1, -1)},
   {Map::Coordinates(1, 1)},
   {Map::Coordinates(-1, 1)},
   {Map::Coordinates(-1, -1)}};
  
GomokuReferee::GomokuReferee(Map &map) : _map(map), _whiteCapturedPieces(0), _blackCapturedPieces(0)
{}

GomokuReferee::~GomokuReferee()
{}

/*
** Check player action
*/
bool			isSameDirection(Map::Coordinates c1, Map::Coordinates c2)
{
  if (c1 == c2)
    return true;
  if (c1 == Map::Coordinates(0, 1) && c2 == Map::Coordinates(0, -1))
    return true;
  if (c2 == Map::Coordinates(0, 1) && c1 == Map::Coordinates(0, -1))
    return true;
  if (c1 == Map::Coordinates(-1, 0) && c2 == Map::Coordinates(1, 0))
    return true;
  if (c2 == Map::Coordinates(-1, 0) && c1 == Map::Coordinates(1, 0))
    return true;
  if (c1 == Map::Coordinates(-1, -1) && c2 == Map::Coordinates(1, 1))
    return true;
  if (c2 == Map::Coordinates(-1, -1) && c1 == Map::Coordinates(1, 1))
    return true;
  if (c2 == Map::Coordinates(1, -1) && c1 == Map::Coordinates(-1, 1))
    return true;
  if (c1 == Map::Coordinates(1, -1) && c2 == Map::Coordinates(-1, 1))
    return true;
  return false;
}

Map::Coordinates		getOppositeDirection(Map::Coordinates c)
{
  if (c == Map::Coordinates(0, 1))	// N
    return Map::Coordinates(0, -1);	// 
  if (c == Map::Coordinates(0, -1))	// S
    return Map::Coordinates(0, 1);	//
  if (c == Map::Coordinates(-1, -1))	// NW
    return Map::Coordinates(1, 1);	//
  if (c == Map::Coordinates(1, 1))	// SE
    return Map::Coordinates(-1, -1);	//
  if (c == Map::Coordinates(1, 0))	// E
    return Map::Coordinates(-1, 0);	//
  if (c == Map::Coordinates(-1, 0))	// W
    return Map::Coordinates(1, 0);	//
  if (c == Map::Coordinates(1, -1))	// NE
    return Map::Coordinates(-1, 1);	//
  if (c == Map::Coordinates(-1, 1))	// SW
    return Map::Coordinates(1, -1);	//
  return Map::Coordinates(-20, -20);
}

std::unique_ptr<std::vector<Map::Coordinates>>	GomokuReferee::testPattern2inDirection(const Map::Coordinates &coordinates, Map::Coordinates direction)
{
  std::vector<Map::Coordinates> *v = new std::vector<Map::Coordinates>;
  std::unique_ptr<std::vector<Map::Coordinates> > pV(v); 
  Map::Coordinates	pos(coordinates);
  int			i = 0;
  int			count = 0;
  int			countEmpty = 0;
  
  pV->push_back(direction);
  if (_map.getCaseAt(pos) != _pawnToCheck)
    return nullptr;
  while (i < 4)
    {
      if (_map.getCaseAt(pos) == _pawnToCheck)
	count++;	  
      if (_map.getCaseAt(pos) == 0)
	countEmpty++;
      pV->push_back(pos);
      if (i < 3)
	pos = pos + direction;
      i++;
    }
  if (_map.getCaseAt(pos) != _pawnToCheck)
    return nullptr;
  if (count == 3 && countEmpty == 1)
    {
      if (!checkIfFree(*pV))
	return pV;
    }
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates>>	GomokuReferee::testPattern1inDirection(const Map::Coordinates &coordinates, Map::Coordinates direction)
{
  std::vector<Map::Coordinates> *v = new std::vector<Map::Coordinates>;
  int			i = 0;
  int			count = 0;
  int			countEmpty = 0;
  Map::Coordinates	pos(coordinates);

  v->push_back(direction);
  while (i < 3)
    {
      if (_map.getCaseAt(pos) == _pawnToCheck)
	count++;
      else if (_map.getCaseAt(pos) == 0)
	countEmpty++;
      v->push_back(pos);
      pos = pos + direction;
      i++;
    }
  if (count == 3 && countEmpty == 0)
    {
      if (!checkIfFree(*v))
	return std::unique_ptr<std::vector<Map::Coordinates> >(v);
    }
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates>> GomokuReferee::testPattern1(const Map::Coordinates &coordinates)
{
  std::unique_ptr<std::vector<Map::Coordinates>> v;
  DirectionsHelper helper;

  for (unsigned int i = 0; i < 8; ++i)
    {
      Map::Coordinates directionToTest = helper.getNextDirection();
      if ((v = testPattern1inDirection(coordinates, directionToTest)) != nullptr) // NORTH
	return v;
    }
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates>> GomokuReferee::testPattern1(const Map::Coordinates &coordinates, Map::Coordinates forbiddenDir)
{
  std::unique_ptr<std::vector<Map::Coordinates>> v;
  DirectionsHelper helper;

  for (unsigned int i = 0; i < 8; ++i)
    {
      Map::Coordinates directionToTest = helper.getNextDirection();

      if (!isSameDirection(directionToTest, forbiddenDir))
	{
	  if ((v = testPattern1inDirection(coordinates, directionToTest)) != nullptr) // NORTH
	    return v;
	}
    }
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates>> GomokuReferee::testPattern2(const Map::Coordinates &coordinates)
{
  std::unique_ptr<std::vector<Map::Coordinates>> v;
  DirectionsHelper helper;

  for (unsigned int i = 0; i < 8; ++i)
    {
      Map::Coordinates directionToTest = helper.getNextDirection();
      if ((v = testPattern2inDirection(coordinates, directionToTest)) != nullptr) // NORTH
	return v;
    }
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates>> GomokuReferee::testPattern2(const Map::Coordinates &coordinates, Map::Coordinates forbiddenDir)
{
  std::unique_ptr<std::vector<Map::Coordinates>> v;
  DirectionsHelper helper;

  for (unsigned int i = 0; i < 8; ++i)
    {
      Map::Coordinates directionToTest = helper.getNextDirection();
      if (!isSameDirection(directionToTest,forbiddenDir))
	{
	  if ((v = testPattern2inDirection(coordinates, directionToTest)) != nullptr) // NORTH
	    return v;
	}
    }
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates>>	GomokuReferee::FindPattern3inLine(Map::Coordinates coordinates)
{
  std::unique_ptr<std::vector<Map::Coordinates>> pV;

  if ((pV = testPattern1(coordinates)) != nullptr)
    return pV;
  Map::Coordinates S(coordinates + Map::Coordinates(0, 1));
  if ((pV = testPattern1inDirection(S, Map::Coordinates(0, -1))) != nullptr)
    return pV;
  Map::Coordinates SW(coordinates + Map::Coordinates(-1, 1));
  if ((pV = testPattern1inDirection(SW, Map::Coordinates(1, -1))) != nullptr)
    return pV;
  Map::Coordinates SE(coordinates + Map::Coordinates(1, 1));
  if ((pV = testPattern1inDirection(SE, Map::Coordinates(-1, -1))) != nullptr)
    return pV;
  Map::Coordinates E(coordinates + Map::Coordinates(-1, 0));
  if ((pV = testPattern1inDirection(E, Map::Coordinates(1, 0))) != nullptr)
    return pV;
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates>>	GomokuReferee::FindPattern3inLine(Map::Coordinates coordinates, Map::Coordinates forbiddenDir)
{
  std::unique_ptr<std::vector<Map::Coordinates>> pV;

  if ((pV = testPattern1(coordinates, forbiddenDir)) != nullptr)
    return pV;
  Map::Coordinates S(coordinates + Map::Coordinates(0, 1));
  if (!isSameDirection(Map::Coordinates(0, 1), forbiddenDir))
    {
      if ((pV = testPattern1inDirection(S, Map::Coordinates(0, -1))) != nullptr)
	return pV;
    }
  Map::Coordinates SW(coordinates + Map::Coordinates(-1, 1));
  if (!isSameDirection(Map::Coordinates(-1, 1), forbiddenDir))
    {
      if ((pV = testPattern1inDirection(SW, Map::Coordinates(1, -1))) != nullptr)
	return pV;
    }
  Map::Coordinates SE(coordinates + Map::Coordinates(1, 1));
  if (!isSameDirection(Map::Coordinates(1, 1), forbiddenDir))
    {
      if ((pV = testPattern1inDirection(SE, Map::Coordinates(-1, -1))) != nullptr)
	return pV;
    }
  Map::Coordinates E(coordinates + Map::Coordinates(-1, 0));
  if (!isSameDirection(Map::Coordinates(-1, 0), forbiddenDir))
    {
      if ((pV = testPattern1inDirection(E, Map::Coordinates(1, 0))) != nullptr)
	return pV;
    }
  return nullptr;
}

std::unique_ptr<std::vector<Map::Coordinates> > GomokuReferee::FindPattern2inLine1Empty(Map::Coordinates coordinates)
{
  std::unique_ptr<std::vector<Map::Coordinates>> pV;

  if ((pV = testPattern2(coordinates)) != nullptr)
    return pV;
  Map::Coordinates N(coordinates + Map::Coordinates(0, -1));
  if ((pV = testPattern2inDirection(N, Map::Coordinates(0, 1))) != nullptr)
    return pV;
  Map::Coordinates S(coordinates + Map::Coordinates(0, 1));
  if ((pV = testPattern2inDirection(S, Map::Coordinates(0, -1))) != nullptr)
    return pV;
  Map::Coordinates SW(coordinates + Map::Coordinates(-1, 1));
  if ((pV = testPattern2inDirection(SW, Map::Coordinates(1, -1))) != nullptr)
    return pV;
  Map::Coordinates NE(coordinates + Map::Coordinates(1, -1));
  if ((pV = testPattern2inDirection(NE, Map::Coordinates(-1, 1))) != nullptr)
    return pV;
  Map::Coordinates NW(coordinates + Map::Coordinates(-1, -1));
  if ((pV = testPattern2inDirection(NW, Map::Coordinates(1, 1))) != nullptr)
    return pV;
  Map::Coordinates SE(coordinates + Map::Coordinates(1, 1));
  if ((pV = testPattern2inDirection(SE, Map::Coordinates(-1, -1))) != nullptr)
    return pV;
  Map::Coordinates E(coordinates + Map::Coordinates(-1, 0));
  if ((pV = testPattern2inDirection(E, Map::Coordinates(1, 0))) != nullptr)
    return pV;
  Map::Coordinates W(coordinates + Map::Coordinates(1, 0));
  if ((pV = testPattern2inDirection(W, Map::Coordinates(-1, 0))) != nullptr)
    return pV;
  return nullptr;
}

bool			GomokuReferee::checkIfFree(const std::vector<Map::Coordinates> &v)
{
  int i = v.size() - 1;
  Map::Coordinates	ex1(v[1] + getOppositeDirection(v[0]));
  Map::Coordinates	ex2(v[i] + v[0]);
  if (ex1.x < 0 || ex1.x > 18)
    return true;
  if (ex1.y < 0 || ex1.y > 18)
    return true;
  if (ex2.x < 0 || ex2.x > 18)
    return true;
  if (ex2.y < 0 || ex2.y > 18)
    return true;
  if (_map.getCaseAt(ex1) == 0 && _map.getCaseAt(ex2) == 0)
    return false;
  return true;
}

std::unique_ptr<std::vector<Map::Coordinates>> GomokuReferee::FindPattern2inLine1Empty(Map::Coordinates coordinates, Map::Coordinates forbiddenDir)
{
  std::unique_ptr<std::vector<Map::Coordinates>> pV;

  if ((pV = testPattern2(coordinates, forbiddenDir)) != nullptr)
    return pV;
  Map::Coordinates N(coordinates + Map::Coordinates(0, -1));
  if (!isSameDirection(forbiddenDir, Map::Coordinates(0, -1)))
    {
      if ((pV = testPattern2inDirection(N, Map::Coordinates(0, 1))) != nullptr)
	return pV;
    }
  Map::Coordinates S(coordinates + Map::Coordinates(0, 1));
  if (!isSameDirection(forbiddenDir, Map::Coordinates(0, 1)))
    {
      if ((pV = testPattern2inDirection(S, Map::Coordinates(0, -1))) != nullptr)
	return pV;
    }
  Map::Coordinates SW(coordinates + Map::Coordinates(-1, 1));
  if (!isSameDirection(forbiddenDir, Map::Coordinates(-1, 1)))
    {
      if ((pV = testPattern2inDirection(SW, Map::Coordinates(1, -1))) != nullptr)
	return pV;
    }
  Map::Coordinates NE(coordinates + Map::Coordinates(1, -1));
  if (!isSameDirection(forbiddenDir, Map::Coordinates(1, -1)))
    {
      if ((pV = testPattern2inDirection(NE, Map::Coordinates(-1, 1))) != nullptr)
	return pV;
    }
  Map::Coordinates NW(coordinates + Map::Coordinates(-1, -1)); 
  if (!isSameDirection(forbiddenDir, Map::Coordinates(-1, -1)))
    {
      if ((pV = testPattern2inDirection(NW, Map::Coordinates(1, 1))) != nullptr)
	return pV;
    }
  Map::Coordinates SE(coordinates + Map::Coordinates(1, 1));
  if (!isSameDirection(forbiddenDir, Map::Coordinates(1, 1)))
    {
      if ((pV = testPattern2inDirection(SE, Map::Coordinates(-1, -1))) != nullptr)
	return pV;
    }
  Map::Coordinates E(coordinates + Map::Coordinates(-1, 0));
  if (!isSameDirection(forbiddenDir, Map::Coordinates(-1, 0)))
    {
      if ((pV = testPattern2inDirection(E, Map::Coordinates(1, 0))) != nullptr)
	return pV;
    }
  Map::Coordinates W(coordinates + Map::Coordinates(1, 0));
  if (!isSameDirection(forbiddenDir, Map::Coordinates(1, 0)))
    {
      if ((pV = testPattern2inDirection(W, Map::Coordinates(-1, 0))) != nullptr)
	return pV;
    }
  return nullptr;
}

bool			GomokuReferee::testDoubleThree(Map::Coordinates coordinates)
{
  std::unique_ptr<std::vector<Map::Coordinates> > pV1 = FindPattern3inLine(coordinates);

  Map::Coordinates				coord;
  if (pV1)
    {
      std::vector<Map::Coordinates> v1 = *(pV1.get());
      for (unsigned int i = 1; i < v1.size(); ++i)
	{
	  std::unique_ptr<std::vector<Map::Coordinates> > pV3 = FindPattern3inLine(v1[i], v1[0]);
	  if (pV3)
	    return true;
	  pV3 = FindPattern2inLine1Empty(v1[i], v1[0]);
	  if (pV3)
	    return true;
	}
    }
  std::unique_ptr<std::vector<Map::Coordinates> > pV2 = FindPattern2inLine1Empty(coordinates);
  if (pV2)
    {
      std::vector<Map::Coordinates> v2 = *(pV2.get());
      for (unsigned int i = 1; i < v2.size(); ++i)
	{
	  std::unique_ptr<std::vector<Map::Coordinates> > pV3 = FindPattern3inLine(v2[i], v2[0]);
	  if (pV3)
	    return true;
	  pV3 = FindPattern2inLine1Empty(v2[i], v2[0]);
	  if (pV3)
	    return true;
	}
    }
  return false;
}

void			GomokuReferee::resetReferee()
{
  this->_whiteCapturedPieces = 0;
  this->_blackCapturedPieces = 0;
}

IReferee::GameState	GomokuReferee::testMap()
{
  IReferee::GameState	state;
  std::vector<int>	vec;

  for (int x = 0; x < MAP_WIDTH; x++)
    {
      for (int y = 0; y < MAP_WIDTH; y++)
	{
	  if (this->_map.getCaseAt(Map::Coordinates(x, y)) != Map::EMPTY)
	    {
	      vec = testAlignement(Map::Coordinates(x, y));
	      for (unsigned int i = 0; i < vec.size(); i++)
		if (vec[i] >= 5)
		  if ((state = TestFiveInARow(x, y, i, this->_map.getCaseAt(Map::Coordinates(x, y)))) != IReferee::GameState::ONGOING)
		    return state;
	    }
	}
    }
  return IReferee::GameState::ONGOING;
}

void			GomokuReferee::setMap(Map &map)
{
  _map = map;
}

IReferee::GameState	GomokuReferee::validatePlayerAction(int CoordX, int CoordY, const bool turn)
{
  setTurn(CoordX, CoordY, turn);

  if (testDoubleThree(Map::Coordinates(CoordX, CoordY)))
    {
      this->_map.setCaseAt(Map::Coordinates((CoordX), (CoordY)), Map::CaseState::EMPTY);
      return IReferee::GameState::UNVALID;
    }

  testCapture(Map::Coordinates(CoordX, CoordY));
  if (this->_whiteCapturedPieces >= 10)
    return IReferee::GameState::P1_WIN;
  else if (this->_blackCapturedPieces >= 10)
    return IReferee::GameState::P2_WIN;

  return testMap();
}

void			GomokuReferee::setTurn(int CoordX, int CoordY, const bool turn)
{
  if (turn)
    {
      _pawnToCheck = Map::CaseState::BLACK;
      _ennemyPawn = Map::CaseState::WHITE;
      this->_map.setCaseAtIndex(MAP_WIDTH * CoordY + CoordX, Map::CaseState::BLACK);
    }
  else
    {
      _pawnToCheck = Map::CaseState::WHITE;
      _ennemyPawn = Map::CaseState::BLACK;
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
		{
		  std::cout << "five in a row can be break" << std::endl;
		  return true;
		}
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

IReferee::GameState		GomokuReferee::TestFiveInARow(int CoordX, int CoordY, int i, Map::CaseState player)
{
  GomokuReferee::Direction	direction;

  direction =
    i == 0 ? GomokuReferee::Direction::SOUTH :
    i == 1 ? GomokuReferee::Direction::EAST :
    i == 2 ? GomokuReferee::Direction::SOUTH_EAST :
    GomokuReferee::Direction::SOUTH_WEST;

  if (hasFiveInARow(direction, Map::Coordinates(CoordX, CoordY)))
    {
      if (player == Map::CaseState::BLACK)
	return IReferee::GameState::P2_WIN;
      else
	return IReferee::GameState::P1_WIN;
    }
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

  if (direction == GomokuReferee::Direction::SOUTH)
    count = countAlignement(coordinates, 0, -1);
  else if (direction == GomokuReferee::Direction::EAST)
    count = countAlignement(coordinates, 1, 0);
  else if (direction == GomokuReferee::Direction::SOUTH_EAST)
    count = countAlignement(coordinates, 1, -1);
  else
    count = countAlignement(coordinates, -1, -1);
  return count + 1;
}

std::vector<int>	GomokuReferee::testAlignement(Map::Coordinates coordinates)
{
  std::vector<int> vec;

  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::EAST, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH_EAST, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH_WEST, coordinates));
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
						  int index,
						  Map::CaseState color)
{
  // int			index = coordinates.y * MAP_WIDTH + coordinates.x;
  int			nextCaseIndex;
  int				count = 0;
  const std::bitset<Map::boardSize>	&bitset = map.getBitSet(color);

  // if (!((coordinates.x == 18
  // 	 && (direction == GomokuReferee::NORTH_EAST
  // 	     || direction == GomokuReferee::SOUTH_EAST
  // 	     || direction == GomokuReferee::EAST))
  // 	|| (coordinates.x == 0
  // 	    && (direction == GomokuReferee::NORTH_WEST
  // 		|| direction == GomokuReferee::SOUTH_WEST
  // 		|| direction == GomokuReferee::WEST))))
  if (abs(index % MAP_WIDTH - (index + direction) % MAP_WIDTH) <= 1)
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
  // if (!((coordinates.x == 18
  // 	 && (-direction == GomokuReferee::NORTH_EAST
  // 	     || -direction == GomokuReferee::SOUTH_EAST
  // 	     || -direction == GomokuReferee::EAST))
  // 	|| (coordinates.x == 0
  // 	    && (-direction == GomokuReferee::NORTH_WEST
  // 		|| -direction == GomokuReferee::SOUTH_WEST
  // 		|| -direction == GomokuReferee::WEST))))
  if (abs(index % MAP_WIDTH - (index - direction) % MAP_WIDTH) <= 1)
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

bool    testCaptureInDirection(GomokuReferee::Direction direction,
			       const Map &map,
			       int index,
			       Map::CaseState color)
{
  Map::CaseState	enemyColor = color == Map::BLACK ? Map::WHITE : Map::BLACK;
  
  if (abs(index % MAP_WIDTH - (index + direction) % MAP_WIDTH) > 1 ||
      index + direction < 0 ||
      index + direction > MAP_SIZE ||
      map.getCaseAtIndex(index + direction) != enemyColor)
    return false;
  if (abs(index % MAP_WIDTH - (index + 2 * direction) % MAP_WIDTH) > 1 ||
      index + 2 * direction < 0 ||
      index + 2 * direction > MAP_SIZE ||
      map.getCaseAtIndex(index + 2 * direction) != enemyColor)
    return false;
  if (abs(index % MAP_WIDTH - (index + 3 * direction) % MAP_WIDTH) > 1 ||
      index + 3 * direction < 0 ||
      index + 3 * direction > MAP_SIZE ||
      map.getCaseAtIndex(index + 3 * direction) != color)
    return false;
  return true;
}
