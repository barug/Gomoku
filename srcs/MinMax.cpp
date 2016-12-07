#include "MinMax.hpp"
#include <iostream>

GomokuMinMax::Result::Result()
  : coordinates(0, 0),
    actionScore(0)
{}

GomokuMinMax::Result::Result(unsigned int x,
			     unsigned int y,
			     int actionScore)
  : coordinates(x, y),
    actionScore(actionScore)
{}

GomokuMinMax::GomokuMinMax()
  : _iaColor(Map::BLACK),
    _enemyColor(Map::WHITE),
    _alpha(12345678)
{}

Map::Coordinates	GomokuMinMax::computeNextAction(const Map &map)
{
  GomokuMinMax::Result	result;

  result = _minMax(map, 0, GomokuMinMax::MAX, 0);
  return (result.coordinates);
}

unsigned int		GomokuMinMax::calculateActionScore(const Map &map,
							   Map::Coordinates Action,
							   bool isIA)
{
  unsigned int		actionScore = 0;

  (void)(isIA);
  for (unsigned int i = 0; i <= 3; i++)
    {
      actionScore += testAlignementInDirection(GomokuReferee::Direction(i),
					       map,
					       Action) - 1;
    }
  for (unsigned int i = 0; i <= 7; i++)
    {
      actionScore += testCaptureInDirection(GomokuReferee::Direction(i), map, Action);
    }
  return actionScore;
}

GomokuMinMax::Result	GomokuMinMax::_minMax(const Map &map,
					      unsigned int depth,
					      GomokuMinMax::turn turn,
					      int actionScore)
{
  // std::cout << "depth: " << depth << std::endl;
  std::vector<char>	mapData = map.getMapData();
  Map			newMap;
  GomokuMinMax::turn	nextTurn;
  GomokuMinMax::Result	bestResult(-1, -1, 12345678);
  GomokuMinMax::Result	result;
  int			resultScore;
  
  if (turn == GomokuMinMax::MIN)
    nextTurn = GomokuMinMax::MAX;
  else
    {
      bestResult.actionScore = -12345678;
      nextTurn = GomokuMinMax::MIN;
    }  
  if (depth < RECURSION_DEPTH)
    {
      depth++;
      for (unsigned int i = 0; i < MAP_SIZE; i++)
	{
	  if (mapData[i] == Map::EMPTY)
	    {
	      newMap = map;
	      if (turn == GomokuMinMax::MAX)
		{
		  newMap.setCaseAtIndex(i, _iaColor);
		  resultScore = calculateActionScore(newMap,
						     Map::Coordinates(i % MAP_WIDTH,
								      i / MAP_WIDTH),
						     true);
		  result = _minMax(newMap, depth, nextTurn, actionScore + resultScore);
		  if (resultScore != 0)
		    {
		      std::cout << "AI result score: " << resultScore;
		      std::cout << " at x: " << i % MAP_WIDTH << " y: "
				<<  i / MAP_WIDTH
				<< std::endl;
		    }
		  if (result.actionScore > bestResult.actionScore)
		    bestResult = result;
		}
	      else
		{
		  newMap.setCaseAtIndex(i, _enemyColor);
		  resultScore = calculateActionScore(newMap,
						     Map::Coordinates(i % MAP_WIDTH,
								      i / MAP_WIDTH),
						     false);
		  result = _minMax(newMap, depth, nextTurn, actionScore - resultScore);
		  if (result.actionScore < bestResult.actionScore)
		    bestResult = result;
		}
	    }
	}
    }
  else
    {
      for (unsigned int i = 0; i < MAP_SIZE; i++)
	{
	  if (mapData[i] == Map::EMPTY)
	    {
	      newMap = map;
	      if (turn == GomokuMinMax::MAX)
		{
		  newMap.setCaseAtIndex(i, _iaColor);
		  resultScore = calculateActionScore(newMap,
						     Map::Coordinates(i % MAP_WIDTH,
								      i / MAP_WIDTH),
						     true);
		  if ((actionScore + resultScore) > bestResult.actionScore)
		    bestResult = GomokuMinMax::Result(i % MAP_WIDTH,
						      i / MAP_WIDTH,
						      actionScore + resultScore);
		}
	      else
		{
		  newMap.setCaseAtIndex(i, _enemyColor);
		  // for (auto tile: newMap.getMapData())
		  //   std::cout << (int)tile;
		  // std::cout << std::endl;
		  // newMap.mapDump();
		  resultScore = calculateActionScore(newMap,
						     Map::Coordinates(i % MAP_WIDTH,
								      i / MAP_WIDTH),
						     false);
		  if (resultScore != 0)
		    {
		      std::cout << "enemy result score: " << resultScore;
		      std::cout << " at x: " << i % MAP_WIDTH << " y: "
				<<  i / MAP_WIDTH
				<< std::endl;
		    }
		  if ((actionScore - resultScore) < bestResult.actionScore)
		    bestResult = GomokuMinMax::Result(i % MAP_WIDTH,
						      i / MAP_WIDTH,
						      actionScore - resultScore);
		}
	    }
	}
    }
  std::cout << "best result : " << result.coordinates.x << " " << result.coordinates.y
  	    << "score: " << result.actionScore << std::endl;
  return (bestResult);
}
