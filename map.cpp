
#include <exception>
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
    throw std::out_of_range;
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
