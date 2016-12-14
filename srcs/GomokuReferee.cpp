// GomokuReferee.cpp for Gomoku in /home/josselin/rendu/tek3/IA/Gomoku/srcs
//
// Made by Josselin
// Login   <josselin@epitech.net>
//
// Started on  Mon Dec  5 13:50:04 2016 Josselin
// Last update Sun Dec 11 23:36:29 2016 Josselin
//

#include <iostream>
#include "GomokuReferee.hpp"

constexpr GomokuReferee::Direction GomokuReferee::directions[8];

GomokuReferee::GomokuReferee(Map &map) : _map(map), _whiteCapturedPieces(0), _blackCapturedPieces(0)
{}

GomokuReferee::~GomokuReferee()
{}


/*
** Check player action
*/
void			GomokuReferee::resetReferee()
{
  this->_whiteCapturedPieces = 0;
  this->_blackCapturedPieces = 0;
}

IReferee::GameState	GomokuReferee::validatePlayerAction(int CoordX, int CoordY, const bool turn)
{
  IReferee::GameState	state;

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

  std::vector<int> vec = testAlignement(Map::Coordinates(CoordX, CoordY));
  for (unsigned int i = 0; i < vec.size(); i++)
    if (vec[i] >= 5)
      if ((state = TestFiveInARow(CoordX, CoordY, i, turn)) != IReferee::GameState::ONGOING)
	return state;
  return IReferee::GameState::ONGOING;
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
      if (turn)
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

  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::WEST, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::NORTH_EAST, coordinates));
  vec.push_back(testAlignementInDirection(GomokuReferee::Direction::SOUTH_EAST, coordinates));
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
** Test Double Trois
*/
bool			GomokuReferee::checkPattern1(Map::Coordinates coordinates, Map::Coordinates direction)
{
  int			i = 0;
  int			count = 0;
  int			countEmpty = 0;

  while (i < 3)
    {
      if (_map.getCaseAt(coordinates) == _pawnToCheck)
	count++;
      else if (_map.getCaseAt(coordinates) == 0)
	countEmpty++;
      coordinates = coordinates + direction;
      i++;
    }
  if (count == 3 && countEmpty == 0)
    return true;
  return false;
}

bool			GomokuReferee::checkPattern2(Map::Coordinates coordinates, Map::Coordinates direction)
{
  bool			mustBePawn;

  if (_map.getCaseAt(coordinates) == _pawnToCheck)
    {
      coordinates = coordinates + direction;
      if (_map.getCaseAt(coordinates) == 0)
	mustBePawn = true;
      else
	mustBePawn = false;
      coordinates = coordinates + direction;
      if (_map.getCaseAt(coordinates) == 0 && mustBePawn == true)
	return false;
      else if (_map.getCaseAt(coordinates) == 0 && mustBePawn == false)
	mustBePawn = true;
      coordinates = coordinates + direction;
      if (_map.getCaseAt(coordinates) == 0 && mustBePawn == true)
	return false;
      else if (_map.getCaseAt(coordinates) == _pawnToCheck && mustBePawn == true)
	return true;
    }
  return false;
}

Map::Coordinates	GomokuReferee::Pattern1(Map::Coordinates coordinates)
{
  if (checkPattern1(coordinates, Map::Coordinates(-1, -1)) == true)
    return (Map::Coordinates(-1, -1));
  if (checkPattern1(coordinates, Map::Coordinates(0, -1)) == true)
    return (Map::Coordinates(0, -1));
  if (checkPattern1(coordinates, Map::Coordinates(1, -1)) == true)
    return (Map::Coordinates(1, -1));
  if (checkPattern1(coordinates, Map::Coordinates(1, 0)) == true)
    return (Map::Coordinates(1, 0));
  if (checkPattern1(coordinates, Map::Coordinates(1, 1)) == true)
    return (Map::Coordinates(1, 1));
  if (checkPattern1(coordinates, Map::Coordinates(0, 1)) == true)
    return (Map::Coordinates(0, 1));
  if (checkPattern1(coordinates, Map::Coordinates(-1, 1)) == true)
    return (Map::Coordinates(-1, 1));
  if (checkPattern1(coordinates, Map::Coordinates(-1, 0)) == true)
    return (Map::Coordinates(-1, 0));
  return (Map::Coordinates(-20, -20));
}

Map::Coordinates	GomokuReferee::Pattern2(Map::Coordinates coordinates)
{
  if (checkPattern2(coordinates, Map::Coordinates(-1, -1)) == true)
    return (Map::Coordinates(-1, -1));
  if (checkPattern2(coordinates, Map::Coordinates(0, -1)) == true)
    return (Map::Coordinates(0, -1));
  if (checkPattern2(coordinates, Map::Coordinates(1, -1)) == true)
    return (Map::Coordinates(1, -1));
  if (checkPattern2(coordinates, Map::Coordinates(1, 0)) == true)
    return (Map::Coordinates(1, 0));
  if (checkPattern2(coordinates, Map::Coordinates(1, 1)) == true)
    return (Map::Coordinates(1, 1));
  if (checkPattern2(coordinates, Map::Coordinates(0, 1)) == true)
    return (Map::Coordinates(0, 1));
  if (checkPattern2(coordinates, Map::Coordinates(-1, 1)) == true)
    return (Map::Coordinates(-1, 1));
  if (checkPattern2(coordinates, Map::Coordinates(-1, 0)) == true)
    return (Map::Coordinates(-1, 0));
  return (Map::Coordinates(-20, -20));
}

bool			GomokuReferee::FindPattern3inLine(std::vector<Map::Coordinates> &v, Map::Coordinates coordinates)
{

  Map::Coordinates	save = coordinates;
  Map::Coordinates	currentCoord(Pattern1(coordinates));
  if (currentCoord != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(save);

      v.push_back(currentCoord);

      v.push_back(save);
      save = save + currentCoord;
      v.push_back(save);
      save = save + currentCoord;
      v.push_back(save);
      if (!(_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn ||
	    _map.getCaseAt(save + currentCoord) == _ennemyPawn))
	return true;
      v.clear();
    }
  coordinates = coordinates + Map::Coordinates(0, 1);
  Map::Coordinates	S(Pattern1(coordinates));
  if (S != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);

      v.push_back(S);

      v.push_back(coordinates);
      coordinates = coordinates + S;
      v.push_back(coordinates);
      coordinates = coordinates + S;
      v.push_back(coordinates);
      if (!(_map.getCaseAt(startingPoint - S) == _ennemyPawn ||
	    _map.getCaseAt(coordinates + S) == _ennemyPawn))
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(-1, 1);
  Map::Coordinates	SW(Pattern1(coordinates));
  if (SW != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);

      v.push_back(SW);

      v.push_back(coordinates);
      coordinates = coordinates + SW;
      v.push_back(coordinates);
      coordinates = coordinates + SW;
      v.push_back(coordinates);
      if (!(_map.getCaseAt(startingPoint - SW) == _ennemyPawn ||
	    _map.getCaseAt(coordinates + SW) == _ennemyPawn))
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(-1, 0);
  Map::Coordinates	W(Pattern1(coordinates));
  if (W != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);

      v.push_back(W);

      v.push_back(coordinates);
      coordinates = coordinates + W;
      v.push_back(coordinates);
      coordinates = coordinates + W;
      v.push_back(coordinates);
      if (!(_map.getCaseAt(startingPoint - W) == _ennemyPawn ||
	    _map.getCaseAt(coordinates + W) == _ennemyPawn))
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(1, 1);
  Map::Coordinates	SE(Pattern1(coordinates));
  if (SE != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);

      v.push_back(SE);

      v.push_back(coordinates);
      coordinates = coordinates + SE;
      v.push_back(coordinates);
      coordinates = coordinates + SE;
      v.push_back(coordinates);
      if (!(_map.getCaseAt(startingPoint - SE) == _ennemyPawn ||
	    _map.getCaseAt(coordinates + SE) == _ennemyPawn))
	return true;
      v.clear();
    }
  return false;
}

bool			GomokuReferee::FindPattern2inLine1Empty(std::vector<Map::Coordinates> &v, Map::Coordinates coordinates)
{
  Map::Coordinates	save = coordinates;
  Map::Coordinates	currentCoord(Pattern2(coordinates));

  if (currentCoord != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(save);
      bool			isBlockable = false;

      v.push_back(currentCoord);

      if (_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn)
	isBlockable = true;
      v.push_back(save);
      save = save + currentCoord;
      if (_map.getCaseAt(save) == _ennemyPawn)
	isBlockable = true;
      save = save + currentCoord;
      if (_map.getCaseAt(save) == _ennemyPawn)
	isBlockable = true;
      save = save + currentCoord;
      v.push_back(save);
      if (isBlockable == false)
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(0, 1);
  Map::Coordinates	S(Pattern2(coordinates));
  if (S != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);
      bool			isBlockable = false;

      v.push_back(S);

      if (_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn)
	isBlockable = true;
      v.push_back(coordinates);
      coordinates = coordinates + S;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + S;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + S;
      v.push_back(coordinates);
      if (isBlockable == false)
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(0, -1);
  Map::Coordinates	N(Pattern2(coordinates));
  if (N != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);
      bool			isBlockable = false;

      v.push_back(N);

      if (_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn)
	isBlockable = true;
      v.push_back(coordinates);
      coordinates = coordinates + N;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + N;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + N;
      v.push_back(coordinates);
      if (isBlockable == false)
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(-1, 1);
  Map::Coordinates	SW(Pattern2(coordinates));
  if (SW != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);
      bool			isBlockable = false;

      v.push_back(SW);

      if (_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn)
	isBlockable = true;
      v.push_back(coordinates);
      coordinates = coordinates + SW;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + SW;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + SW;
      v.push_back(coordinates);
      if (isBlockable == false)
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(1, -1);
  Map::Coordinates	NE(Pattern2(coordinates));
  if (NE != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);
      bool			isBlockable = false;

      v.push_back(NE);

      if (_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn)
	isBlockable = true;
      v.push_back(coordinates);
      coordinates = coordinates + NE;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + NE;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + NE;
      v.push_back(coordinates);
      if (isBlockable == false)
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(1, 1);
  Map::Coordinates	SE(Pattern2(coordinates));
  if (SE != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);
      bool			isBlockable = false;

      v.push_back(SE);

      if (_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn)
	isBlockable = true;
      v.push_back(coordinates);
      coordinates = coordinates + SE;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + SE;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + SE;
      v.push_back(coordinates);
      if (isBlockable == false)
	return true;
      v.clear();
    }
  coordinates = save;
  coordinates = coordinates + Map::Coordinates(-1, -1);
  Map::Coordinates	NW(Pattern2(coordinates));
  if (NW != Map::Coordinates(-20, -20))
    {
      Map::Coordinates	startingPoint(coordinates);
      bool			isBlockable = false;

      v.push_back(NW);

      if (_map.getCaseAt(startingPoint - currentCoord) == _ennemyPawn)
	isBlockable = true;
      v.push_back(coordinates);
      coordinates = coordinates + NW;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + NW;
      if (_map.getCaseAt(coordinates) == _ennemyPawn)
	isBlockable = true;
      coordinates = coordinates + NW;
      v.push_back(coordinates);
      if (isBlockable == false)
	return true;
      v.clear();
    }
  return false;
}

bool			isSameDirection(Map::Coordinates c1, Map::Coordinates c2)
{
  bool			ligne = false;
  bool			diagonale = false;

  if ((c1.x == c2.x || c1.y == c2.x))
    ligne = true;
  if (c1.x == c2.y && c1.y == c2.x)
    diagonale = true;
  if (ligne || diagonale)
    return true;
  return false;
}

bool			GomokuReferee::testDoubleThree(Map::Coordinates coordinates)
{
  std::vector<Map::Coordinates> vP1;
  FindPattern3inLine(vP1, coordinates);
  std::vector<Map::Coordinates> vP2;
  FindPattern2inLine1Empty(vP2, coordinates);

  if (vP1.size() >= 1 && vP2.size() == 0)
    {
      Map::Coordinates		ex1(vP1[1]);
      Map::Coordinates		ex2(vP1[3]);

      std::vector<Map::Coordinates> testEx1;
      std::vector<Map::Coordinates> testEx2;
      if (FindPattern2inLine1Empty(testEx1, ex1) == true ||
	  FindPattern2inLine1Empty(testEx2, ex2) == true)
	{

	  if (testEx1.size() > 0 && testEx2.size() == 0)
	    {
	      bool	extrimitie1;
	      bool	extrimitie2;

	      if (vP1[1] == testEx1[1] || vP1[1] == testEx1[2])
		extrimitie1 = true;
	      if (vP1[3] == testEx1[1] || vP1[3] == testEx1[2])
		extrimitie2 = true;

	      if (!(extrimitie1 || extrimitie2))
		{
		  if (isSameDirection(vP1[0], testEx1[0]) == true)
		    return false;
		}
	    }
	  if (testEx1.size() == 0 && testEx2.size() > 0)
	    {
	      bool	extrimitie1;
	      bool	extrimitie2;

	      if (vP1[1] == testEx2[1] || vP1[1] == testEx2[2])
		extrimitie1 = true;
	      if (vP1[3] == testEx2[1] || vP1[3] == testEx2[2])
		extrimitie2 = true;

	      if (!(extrimitie1 || extrimitie2))
		{
		  if (isSameDirection(vP1[0], testEx2[0]) == true)
		    return false;
		}
	    }
	  return true;
	}
    }
  else if (vP1.size() == 0 && vP2.size() >= 1)
    {
      Map::Coordinates		ex1(vP2[1]);
      Map::Coordinates		ex2(vP2[2]);

      std::vector<Map::Coordinates> testEx1;
      std::vector<Map::Coordinates> testEx2;
      if (FindPattern3inLine(testEx1, ex1) == true ||
	  FindPattern3inLine(testEx2, ex2) == true)
	{
	  if (testEx1.size() > 0 && testEx2.size() == 0)
	    {
	      bool	extrimitie1;
	      bool	extrimitie2;

	      if (vP2[2] == testEx1[1] || vP2[2] == testEx1[3])
		extrimitie1 = true;
	      if (vP2[1] == testEx1[1] || vP2[1] == testEx1[3])
		extrimitie2 = true;

	      if (!(extrimitie1 || extrimitie2))
		{
		  if (!(vP2[1] == testEx1[1] || vP2[2] == testEx1[3]))
		    return false;
		  if (isSameDirection(vP2[0], testEx1[0]) == true)
		    return false;
		}
	    }
	  if (testEx1.size() == 0 && testEx2.size() > 0)
	    {
	      bool	extrimitie1;
	      bool	extrimitie2;

	      if (vP2[2] == testEx2[1] || vP2[2] == testEx2[3])
		extrimitie1 = true;
	      if (vP2[1] == testEx2[1] || vP2[1] == testEx2[3])
		extrimitie2 = true;

	      if (!(extrimitie1 || extrimitie2))
		{
		  if (!(vP2[1] == testEx2[1] || vP2[2] == testEx2[3]) ||
		      !(vP2[2] == testEx2[1] || vP2[2] == testEx2[3]))
		    return false;
		  if (isSameDirection(vP2[0], testEx2[0]) == true)
		    return false;
		}
	    }
	  return true;
	}
    }
  else if (vP1.size() >= 1 && vP2.size() >= 1)
    {
      bool	extrimitie1;
      bool	extrimitie2;

      if (vP2[2] == vP1[1] || vP2[2] == vP1[3])
	extrimitie1 = true;
      if (vP2[1] == vP1[1] || vP2[1] == vP1[3])
	extrimitie2 = true;

      if (!(extrimitie1 || extrimitie2))
	{
	  if (_map.getCaseAt(Map::Coordinates(coordinates + vP1[0])) != _pawnToCheck)
	    return false;
	  if (_map.getCaseAt(Map::Coordinates(coordinates + vP2[0])) != _pawnToCheck)
	    return false;
	}
      return true;
    }
  return false;
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
  int			index = coordinates.y * MAP_WIDTH + coordinates.x;
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
