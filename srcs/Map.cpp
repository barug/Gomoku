//
// map.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 15:28:50 2016 Thomas Billot
// Last update Fri Dec  2 17:40:00 2016 Josselin
//

#include <stdexcept>
#include "Map.hpp"

Map::Map()
  : _mapData(std::vector<Map::CaseState>(MAP_SIZE, Map::EMPTY))
{}

Map::~Map()
{}

Map::Coordinates::Coordinates(const unsigned int &x,
			      const unsigned int &y)
  : x(x),
    y(y)
{}

void				Map::setCaseAt(const Map::Coordinates &coordinates,
					       const Map::CaseState &state)
{
  if ((MAP_WIDTH * coordinates.y + coordinates.x) > MAP_SIZE)
    throw std::out_of_range ("Error in Map::setCaseAt");
  _mapData[MAP_WIDTH * coordinates.y + coordinates.x] = state;
}

const Map::CaseState		&Map::getCaseAt(const Map::Coordinates &coordinates)
{
  return _mapData[MAP_WIDTH * coordinates.y + coordinates.x];
}

const Map::CaseState		&Map::getCaseAtIndex(const int index)
{
  return _mapData[index];
}

const std::vector<Map::CaseState>	&Map::getMapData()
{
  return _mapData;
}
