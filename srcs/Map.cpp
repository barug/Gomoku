//
// map.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 15:28:50 2016 Thomas Billot
// Last update Tue Dec  6 19:09:24 2016 Thomas Billot
//

#include <iostream>
#include <stdexcept>
#include "Map.hpp"

Map::Map()
  : _mapData(std::vector<char>(MAP_SIZE, Map::EMPTY))
{}

Map::Map(std::vector<char> &mapData)
  : _mapData(mapData)
{}

Map::~Map()
{}

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

const char			&Map::getCaseAt(const Map::Coordinates &coordinates) const
{
  return _mapData[MAP_WIDTH * coordinates.y + coordinates.x];
}

const char			&Map::getCaseAtIndex(const int index) const
{
  return _mapData[index];
}

void				Map::setCaseAtIndex(int index, Map::CaseState state)
{
  _mapData[index] = state;
}

const std::vector<char>		&Map::getMapData() const
{
  return _mapData;
}

void				Map::mapDump() const
{
  std::cout << "map dump: ----------------";
  for (int i = 0; i < MAP_SIZE; i++)
    {
      if (i % MAP_WIDTH == 0)
	std::cout << std::endl;
      std::cout << (int)_mapData[i];
    }
  std::cout << std::endl;
}
