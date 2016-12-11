//
// map.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 15:28:50 2016 Thomas Billot
// Last update Sat Dec 10 00:47:26 2016 Thomas Billot
//

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Map.hpp"

Map::Map()
{}

Map::Map(std::vector<char> initVect)
{
  for (unsigned int i = 0; i < initVect.size(); i++)
    {
      if (initVect[i] == Map::WHITE)
	_whiteBoard[i] = true;
      if (initVect[i] == Map::BLACK)
	_blackBoard[i] = true;
    }
}

Map::Map(Map &map)
  : _whiteBoard(map._whiteBoard),
    _blackBoard(map._blackBoard)
{}

Map::~Map()
{}

void			        Map::resetAllCases()
{
  for (unsigned int i = 0; i < (Map::boardSize - 1); i++)
    {
      _whiteBoard.set(i,false);
      _blackBoard.set(i,false);
    }
}

int				Map::convertToIndex(const Map::Coordinates &coord) const
{
  return boardWidth * coord.y + coord.x;
}

void				Map::setCaseAt(const Map::Coordinates &coordinates,
					       const Map::CaseState &state)
{
  unsigned int index = convertToIndex(coordinates);
  if (state == Map::EMPTY)
    {
      _blackBoard[index] = false;
      _whiteBoard[index] = false;
      _pawnOnBoardIndexes.erase(std::remove(_pawnOnBoardIndexes.begin(),
					    _pawnOnBoardIndexes.end(),
					    index),
			        _pawnOnBoardIndexes.end());
      return;
    }
  if (state == Map::BLACK)
    _blackBoard[index] = true;
  else
    _whiteBoard[index] = true;
  _pawnOnBoardIndexes.push_back(index);
}

void				Map::setCaseAtIndex(int index, Map::CaseState state)
{
  if (state == Map::EMPTY)
    {
      _blackBoard[index] = false;
      _whiteBoard[index] = false;
      _pawnOnBoardIndexes.erase(std::remove(_pawnOnBoardIndexes.begin(),
					    _pawnOnBoardIndexes.end(),
					    index),
			        _pawnOnBoardIndexes.end());
      return;
    }
  if (state == Map::BLACK)
    _blackBoard[index] = true;
  else
    _whiteBoard[index] = true;
  _pawnOnBoardIndexes.push_back(index);
}

Map::CaseState 			Map::getCaseAt(const Map::Coordinates &coordinates) const
{
  if (convertToIndex(coordinates) < 0 || convertToIndex(coordinates) > Map::boardSize)
    return Map::EMPTY;
  if (_blackBoard[convertToIndex(coordinates)])
    return Map::BLACK;
  if (_whiteBoard[convertToIndex(coordinates)])
    return Map::WHITE;
  return Map::EMPTY;
}

Map::CaseState			Map::getCaseAtIndex(const int index) const
{
  if (_blackBoard[index])
    return Map::BLACK;
  if (_whiteBoard[index])
    return Map::WHITE;
  return Map::EMPTY;
}

const std::bitset<Map::boardSize>	&Map::getBitSet(Map::CaseState color) const 
{
  if (color == Map::WHITE)
    return _whiteBoard;
  else
    return _blackBoard;
}

const std::vector<unsigned int>		&Map::GetPawnBoardIndexes() const
{
  return _pawnOnBoardIndexes;
}

// void				Map::mapDump() const
// {
//   std::cout << "map dump: ----------------";
//   for (int i = 0; i < MAP_SIZE; i++)
//     {
//       if (i % MAP_WIDTH == 0)
// 	std::cout << std::endl;
//       std::cout << (int)_mapData[i];
//     }
//   std::cout << std::endl;
// }
