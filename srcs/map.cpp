//
// map.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Wed Nov 30 15:28:50 2016 Thomas Billot
// Last update Wed Nov 30 15:30:27 2016 Thomas Billot
//

#include <stdexcept>
#include "map.hpp"

Map::Map()
  : _mapData(std::vector<char>(MAP_SIZE, Map::EMPTY))
{}

Map::~Map()
{}

void				Map::setCaseAt(const unsigned int &x,
					       const unsigned int &y,
					       const Map::CaseState &state)
{
  if ((MAP_WIDTH * y + x) > MAP_SIZE)
    throw std::out_of_range ("Error in Map::setCaseAt");
  _mapData[MAP_WIDTH * y + x] = state;
}

const Map::CaseState		&Map::getCaseAt(const unsigned int &x,
						const unsigned int &y)
{
  return _mapData[MAP_WIDTH * y + x];
}

const std::vector<char>		&Map::getMapData()
{
  return _mapData;
}
