#include "Referee.hpp"

GomokuReferee::GomokuReferee()
{}

GomokuReferee::~GomokuReferee()
{}

IReferee::gameState	GomokuReferee::validatePlayerAction(const unsigned int &CoordX,
							    const unsigned int &CoordY)
{}

int			countAlignement(const Map &map, Map::Coordinates coordinates, int xInc, int yInc)
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

bool				countCapture(const Map &map, Map::Coordinates coordinates, int xInc, int yInc)
{
  Map::CaseState rivals = map[MAP_WIDTH * coordinates.y + coordinates.x] == Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;

  if (map[MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)] == rivals &&
      map[MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2))] == rivals &&
      map[MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))] == map[MAP_WIDTH * coordinates.y + coordinates.x])
    return true;
  return false;
}

bool				testCapture(GomokuReferee::Direction direction,
					    const Map &map, Map::Coordinates coordinates)
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
    }
  if (MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3)) > MAP_SIZE)
    return false;
  return countCapture(map, coordinates, xInc, yInc);
}
