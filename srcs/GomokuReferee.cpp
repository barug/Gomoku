#include "GomokuReferee.hpp"

GomokuReferee::GomokuReferee(Map &map) : _map(map)
{}

GomokuReferee::~GomokuReferee()
{}

IReferee::gameState	GomokuReferee::validatePlayerAction(const unsigned int &,
							    const unsigned int &)
{
  return IReferee::gameState::ONGOING;
}

int			countAlignement(Map &map,
					Map::Coordinates coordinates,
					int xInc,
					int yInc)
{
  int			count = 0;

  while (MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc) <= MAP_SIZE &&
	 map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
	 map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)))
    {
      xInc = xInc < 0 ? xInc - 1 : xInc > 0 ? xInc + 1 : 0;
      yInc = yInc < 0 ? yInc - 1 : yInc > 0 ? yInc + 1 : 0;
      count++;
    }
  return count;
}

int				testAlignement(GomokuReferee::Direction direction,
					       Map &map,
					       Map::Coordinates coordinates)
{
  int				count;

  if (direction == GomokuReferee::Direction::NORTH || direction == GomokuReferee::Direction::SOUTH)
    count = countAlignement(map, coordinates, 0, 1) + countAlignement(map, coordinates, 0, -1);
  else if (direction == GomokuReferee::Direction::WEST || direction == GomokuReferee::Direction::EAST)
    count = countAlignement(map, coordinates, 1, 0) + countAlignement(map, coordinates, -1, 0);
  else if (direction == GomokuReferee::Direction::NORTH_EAST || direction == GomokuReferee::Direction::SOUTH_WEST)
    count = countAlignement(map, coordinates, 1, 1) + countAlignement(map, coordinates, -1, -1);
  else
    count = countAlignement(map, coordinates, 1, -1) + countAlignement(map, coordinates, -1, 1);
  return count;
}

bool				countCapture(Map &map, Map::Coordinates coordinates, int xInc, int yInc)
{
  Map::CaseState rivals = map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) == Map::CaseState::WHITE ? Map::CaseState::BLACK : Map::CaseState::WHITE;

  if (map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)) == rivals &&
      map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2))) == rivals &&
      map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))) == map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x))
    return true;
  return false;
}
bool				testCaptureInDirection(GomokuReferee::Direction direction,
						       Map &map,
						       Map::Coordinates coordinates)
{
  int xInc = 0;
  int yInc = 0;
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

std::vector<GomokuReferee::Direction>	testCapture(Map &map, Map::Coordinates coordinates)
{
  std::vector<GomokuReferee::Direction> captureDirection;

  if (testCaptureInDirection(GomokuReferee::Direction::NORTH, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::NORTH);
  if (testCaptureInDirection(GomokuReferee::Direction::NORTH_EAST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::NORTH_EAST);
  if (testCaptureInDirection(GomokuReferee::Direction::EAST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::EAST);
  if (testCaptureInDirection(GomokuReferee::Direction::SOUTH_EAST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::SOUTH_EAST);
  if (testCaptureInDirection(GomokuReferee::Direction::SOUTH, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::SOUTH);
  if (testCaptureInDirection(GomokuReferee::Direction::SOUTH_WEST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::SOUTH_WEST);
  if (testCaptureInDirection(GomokuReferee::Direction::WEST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::WEST);
  if (testCaptureInDirection(GomokuReferee::Direction::NORTH_WEST, map, coordinates))
    captureDirection.push_back(GomokuReferee::Direction::NORTH_WEST);
  return captureDirection;
}
