//
// Map.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Wed Nov 30 12:41:17 2016 Thomas Billot
// Last update Wed Nov 30 13:22:51 2016 Thomas Billot
//

#include	<iostream>
#include	"Map.hpp"

Map::Map() : _map()
{
  for (unsigned int x = 0; x < Map::mapSize; x++)
    {
      for (unsigned int y = 0; y < Map::mapSize; y++)
	{
	  Case *tmp = new Case(x,
			       y,
			       Map::offsetMapX + (x * Map::offsetX),
			       Map::offsetMapY + (y * Map::offsetY));
	  _map.push_back(std::move(std::unique_ptr<Case*>(&tmp)));
	}
    }
} 

void		Map::update(IGui &gui)
{
  for (unsigned int x = 0; x < Map::mapSize; x++)
    {
      for (unsigned int y = 0; x < Map::mapSize; y++)
	{
	  if (x != 18 && y != 18)
	    {
	      gui->fillRec(Map::offsetMapX + (x * map::offsetX), 30);
	    }
	}
    }
}
