//
// map.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 15:28:50 2016 Thomas Billot
// Last update Tue Dec  6 12:02:11 2016 Thomas Billot
//

#include <stdexcept>
#include "Map.hpp"

Map::Map()
  : _mapData(std::vector<Map::CaseState>(MAP_SIZE, Map::EMPTY))
{}

Map::~Map()
{}

Map::Coordinates::Coordinates(const unsigned int x,
			      const unsigned int y)
  : x(x),
    y(y)
{}

int				Map::Coordinates::getX() const
{
  return x;
}

int				Map::Coordinates::getY() const
{
  return y;
}

Map::Coordinates		Map::Coordinates::operator+(const Map::Coordinates &rhs)
{
  return Coordinates(x + rhs.getX(), y + rhs.getY());
}

Map::Coordinates	        Map::Coordinates::operator-(const Map::Coordinates &rhs)
{
  return Coordinates(x - rhs.getX(), y - rhs.getY());
}

bool				Map::Coordinates::operator==(const Map::Coordinates &rhs)
{
  return x == rhs.getX() && y == rhs.getY();
}

void			        Map::resetAllCases(const unsigned int size)
{
  for (unsigned int x = 0; x < size; x++)
    for (unsigned int y = 0; y < size; y++)
      setCaseAt(Map::Coordinates(x, y), Map::CaseState::EMPTY);
}

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
