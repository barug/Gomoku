#include "MinMax.hpp"
#include <iostream>
#include <cmath>

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

GomokuMinMax::GomokuMinMax(Map::CaseState iaColor)
  : _iaColor(iaColor)
{
  if (_iaColor == Map::BLACK)
    _enemyColor = Map::WHITE;
  else
    _enemyColor = Map::BLACK;
}

GomokuMinMax::GomokuMinMax()
  : _iaColor(Map::BLACK),
    _enemyColor(Map::WHITE)
{}

Map::Coordinates	*GomokuMinMax::computeNextAction(const Map &map)
{
  GomokuMinMax::Result	result;

  result = _minMax(map, 0, -12345678, 12345678, GomokuMinMax::MAX, 0);
  return (new Map::Coordinates(result.coordinates));
}

unsigned int		GomokuMinMax::calculateActionScore(const Map &map,
							   Map::Coordinates Action,
							   Map::CaseState color)
{
  unsigned int		actionScore = 0;
  Map::CaseState	enemyColor = color == Map::WHITE ? Map::BLACK : Map::WHITE;
  unsigned int		testResult;
  
  for (unsigned int i = 0; i <= 3; i++)
    {
      testResult = pow(testAlignementInDirection(GomokuReferee::directions[i],
						 map,
						 Action,
						 color), 2);
      if (testResult == 25)
	testResult = 12345678;
      actionScore += testResult;
      actionScore += pow(testAlignementInDirection(GomokuReferee::directions[i],
						   map,
						   Action,
						   enemyColor), 2);
    }
  for (unsigned int i = 0; i <= 7; i++)
    {
      // actionScore += testCaptureInDirection(GomokuReferee::directions[i], map, Action);
      
    }
  return actionScore;
}

GomokuMinMax::Result	GomokuMinMax::_minMax(const Map &map,
					      unsigned int depth,
					      int alpha,
					      int beta,
					      GomokuMinMax::turn turn,
					      int actionScore)
{
  Map			newMap;
  Map::Coordinates	nextMove;
  GomokuMinMax::turn	nextTurn;
  GomokuMinMax::Result	bestResult(0, 0,  12345678);
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
	  if (map.getCaseAtIndex(i) == Map::EMPTY)
	    {
	      newMap = map;
	      nextMove.x = i % MAP_WIDTH;
	      nextMove.y = i / MAP_WIDTH;
	      if (turn == GomokuMinMax::MAX)
		{
		  newMap.setCaseAtIndex(i, _iaColor);
		  resultScore = calculateActionScore(newMap,
						     nextMove,
						     _iaColor);
		  result = _minMax(newMap, depth, alpha, beta, nextTurn, actionScore + resultScore);
		  // if (resultScore != 0)
		  //   {
		  //     std::cout << "AI result score: " << resultScore;
		  //     std::cout << " at x: " << i % MAP_WIDTH << " y: "
		  // 		<<  i / MAP_WIDTH
		  // 		<< std::endl;
		  //   }
		  if (result.actionScore > alpha)
		    {
		      alpha = result.actionScore;
		      bestResult.coordinates.x = nextMove.x;
		      bestResult.coordinates.y = nextMove.y;
		      bestResult.actionScore = result.actionScore;
		      if (alpha >= beta)
			return bestResult;
		    }
		  // if (result.actionScore > bestResult.actionScore)
		  //   {
		  //     result.coordinates.x = i % MAP_WIDTH;
		  //     result.coordinates.y = i / MAP_WIDTH;
		      // std::cout << "found new best result score: "
		      // 		<< result.actionScore
		      // 		<< " at x: " << result.coordinates.x
		      // 		<< " y: " << result.coordinates.y << std::endl;
		    //   bestResult = result;
		    // }
		}
	      else
		{
		  newMap.setCaseAtIndex(i, _enemyColor);
		  resultScore = calculateActionScore(newMap,
						     nextMove,
						     _enemyColor);
		  result = _minMax(newMap, depth, alpha, beta, nextTurn, actionScore - resultScore);
		  if (result.actionScore < beta)
		    {
		      beta = result.actionScore;
		      bestResult.coordinates.x = nextMove.x;
		      bestResult.coordinates.y = nextMove.y;
		      bestResult.actionScore = result.actionScore;
		      if (alpha >= beta)
			return bestResult;
		    }
		}
	    }
	}
    }
  else
    {
      for (unsigned int i = 0; i < MAP_SIZE; i++)
	{
	  if (map.getCaseAtIndex(i) == Map::EMPTY)
	    {
	      newMap = map;
	      nextMove.x = i % MAP_WIDTH;
	      nextMove.y = i / MAP_WIDTH;
	      if (turn == GomokuMinMax::MAX)
		{
		  newMap.setCaseAtIndex(i, _iaColor);
		  resultScore = calculateActionScore(newMap,
						     nextMove,
						     _iaColor);
		  if ((actionScore + resultScore) > alpha)
		    {
		      alpha = actionScore + resultScore;
		      bestResult.actionScore = alpha;
		      if (alpha >= beta)
			return bestResult;
		    }
		}
	      else
		{
		  // std::cout << "enemy testing for x: " << i % MAP_WIDTH << " y: "
		  // 	    <<  i / MAP_WIDTH
		  // 	    << std::endl;

		  newMap.setCaseAtIndex(i, _enemyColor);
		  // for (auto tile: newMap.getMapData())
		  //   std::cout << (int)tile;
		  // std::cout << std::endl;
		  // newMap.mapDump();
		  resultScore = calculateActionScore(newMap,
						     nextMove,
						     _enemyColor);
		  // if (resultScore != 0)
		  //   {
		      // std::cout << "enemy result score: " << resultScore;
		      // std::cout << " at x: " << i % MAP_WIDTH << " y: "
		      // 		<<  i / MAP_WIDTH
		      // 		<< std::endl;
		    // }
		  if ((actionScore - resultScore) < beta)
		    {
		      beta = actionScore - resultScore;
		      bestResult.actionScore = actionScore - resultScore;
		      if (beta <= alpha)
			return bestResult;
		    }
		}
	    }
	}
    }
  // std::cout << "best result : " << result.coordinates.x << " " << result.coordinates.y
  // 	    << "score: " << result.actionScore << std::endl;
  return (bestResult);
}
