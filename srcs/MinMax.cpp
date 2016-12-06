#include "MinMax.hpp"

GomokuMinMax::Result::Result(unsigned int x,
			     unsigned int y,
			     unsigned int actionScore)
  : coordinates(x, y),
    actionScore(actionScore)
{}

GomokuMinMax::GomokuMinMax()
  : _alpha(12345678),
    _iaColor(Map::Black)
{}

Map::Coordinates	GomokuMinMax::computeNextAction(const Map &map)
{
  GomokuMinMax::Result	result;

  result = _minMax(map, 0, GomokuMinMax::MAX);
  return (result.Coordinates);
}

unsigned int		GomokuMinMax::CalculateActionScore(const Map &map,
							   Map::Coordinates Action,
							   
GomokuMinMax::Result	GomokuMinMax::_minMax(const Map map,
					      unsigned int depth,
					      GomokuMinMax::turn turn)
{
  std::vector<char>	mapData = map.getMapData();
  Map			newMap;
  GomokuMinMax::turn	nextTurn;
  GomokuMinMax::Result	bestResult(-1, -1, 12345678);
  GomokuMinMax::Result	result;

  if (turn == GomokuMinMax::MIN)
    nextTurn = GomokuMinMax::Max;
  else
    {
      bestResult.actionScore = -12345678;
      nextTurn = GomokuMinMax::MIN;
    }
  
  if (depth < RECURSION_DEPTH)
    {
      for (unsigned int i = 0; i < MAP_SIZE; i++)
	{
	  if (mapData[i] == Map::EMPTY)
	    {
	      newMap = map;
	      if (turn == GomokuMinMax::MAX)
		{
		  newMap.getMapData()[i] = _iaColor;
		  result = _minMax(newMap, ++depth, nextTurn);
		  if (result.actionScore > bestResult.actionScore)
		    bestResult = result;
		}
	      else
		{
		  newMap.getMapData()[i] = _enemyColor;
		  result = _minMax(newMap, ++depth, nextTurn);
		  if (result.actionScore < bestResult.actionScore)
		    bestResult = result;
		}
	    }
	}
    }
  else
    {
      
    }
}
