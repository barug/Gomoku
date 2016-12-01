#include "Referee.hpp"

GomokuReferee::GomokuReferee()
{}

GomokuReferee::~GomokuReferee()
{}

IReferee::gameState	GomokuReferee::validatePlayerAction(const unsigned int &CoordX,
							    const unsigned int &CoordY)
{}

int				testAlignement(GomokuReferee::direction direction,
					       const Map &map, Map::Coordinates coordinates)
{
  int				count;
  int				inc = 1;

  if (direction == GomokuReferee::Direction::NORTH ||
      direction == GomokuReferee::Direction::SOUTH)
    {
      while (map[coordinates.x][coordinates.y + inc] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x][coordinates.y + inc++])
	count++;
      inc = -1;
      while (map[coordinates.x][coordinates.y + inc] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x][coordinates.y + inc--])
	count++;
    }
  else if (direction == GomokuReferee::Direction::WEST ||
	   direction == GomokuReferee::Direction::EAST)
    {
      while (map[coordinates.x + inc][coordinates.y] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x + inc++][coordinates.y])
	count++;
      inc = -1;
      while (map[coordinates.x + inc][coordinates.y] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x + inc--][coordinates.y])
	count++;
    }
  else if (direction == GomokuReferee::Direction::NORTH_EAST ||
	   direction == GomokuReferee::Direction::SOUTH_WEST)
    {
      while (map[coordinates.x + inc][coordinates.y + inc] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x + inc][coordinates.y + inc++])
	count++;
      inc = -1;
      while (map[coordinates.x + inc][coordinates.y] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x + inc][coordinates.y + inc--])
	count++;
    }
  else
    {
      int inc_b = -1;
      while (map[coordinates.x + inc][coordinates.y] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x + inc++][coordinates.y + inc_b--])
	count++;
      inc_b = -1;
      inc = 1;
      while (map[coordinates.x + inc][coordinates.y] &&
	     map[coordinates.x][coordinates.y] ==
	     map[coordinates.x + inc_b--][coordinates.y + inc++])
	count++;
    }
  return count;
}

bool				testCapture(GomokuReferee::direction direction,
					    const Map &map, Map::Coordinates coordinates)
{

}
