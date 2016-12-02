#include "Referee.hpp"

GomokuReferee::GomokuReferee()
{}

GomokuReferee::~GomokuReferee()
{}

IReferee::gameState	GomokuReferee::validatePlayerAction(const unsigned int &CoordX,
							    const unsigned int &CoordY)
{}

int			countAlignement(const Map &map, int xInc, int yInc)
{
  int			count = 0;

  while (map[MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)] <= MAP_SIZE &&
	 map[MAP_WIDTH * coordinates.y + coordinates.x] ==
	 map[MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)])
    {
      xInc = xInc < 0 ? xInc - 1 : xInc > 0 ? xInc + 1 : 0;
      yInc = yInc < 0 ? yInc - 1 : yInc > 0 ? yInc + 1 : 0;
      count++;
    }
  return count;
}

int				testAlignement(GomokuReferee::Direction direction,
					       const Map &map, Map::Coordinates coordinates)
{
  int				count;

  if (direction == GomokuReferee::Direction::NORTH || direction == GomokuReferee::Direction::SOUTH)
    count = countAlignement(map, 0, 1) + countAlignement(map, 0, -1);
  else if (direction == GomokuReferee::Direction::WEST || direction == GomokuReferee::Direction::EAST)
    count = countAlignement(map, 1, 0) + countAlignement(map, -1, 0);
  else if (direction == GomokuReferee::Direction::NORTH_EAST || direction == GomokuReferee::Direction::SOUTH_WEST)
    count = countAlignement(map, 1, 1) + countAlignement(map, -1, -1);
  else
    count = countAlignement(map, 1, -1) + countAlignement(map, -1, 1);
  return count;
}

bool				testCapture(GomokuReferee::Direction direction,
					    const Map &map, Map::Coordinates coordinates)
{

}
