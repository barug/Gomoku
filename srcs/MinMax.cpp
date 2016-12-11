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
  int			bestResult = -12345678;
  Map::Coordinates	*bestResultCoordinates = new Map::Coordinates;
  int			actionScore;
  int			resultScore;
  Map			newMap;
  int			alpha = -12345678;
  int			beta = 12345678;
  
  for (unsigned int i = 0; i < MAP_SIZE; i++)
    {
      if (map.getCaseAtIndex(i) == Map::EMPTY)
	{
	  newMap = map;
	  newMap.setCaseAtIndex(i, _iaColor);
	  actionScore = calculateActionScore(newMap,
					     i,
					     _iaColor);
	  resultScore = _minMax(newMap, 0, alpha, beta, GomokuMinMax::MIN, actionScore);
	  if (resultScore > bestResult)
	    {
	      alpha = resultScore;
	      bestResult = resultScore;
	      bestResultCoordinates->x = i % MAP_WIDTH;
	      bestResultCoordinates->y = i / MAP_WIDTH;
	    }
	}
    }
  return (bestResultCoordinates);
}

unsigned int		GomokuMinMax::calculateActionScore(const Map &map,
							   int index,
							   Map::CaseState color)
{
  unsigned int		actionScore = 0;
  Map::CaseState	enemyColor = color == Map::WHITE ? Map::BLACK : Map::WHITE;
  unsigned int		testResult;
  
  for (unsigned int i = 0; i <= 3; i++)
    {
      testResult = pow(testAlignementInDirection(GomokuReferee::directions[i],
						 map,
						 index,
						 color), 2);
      if (testResult == 25)
	testResult = 12345678;
      actionScore += testResult;
      actionScore += pow(testAlignementInDirection(GomokuReferee::directions[i],
						   map,
						   index,
						   enemyColor), 2);
    }
  for (unsigned int i = 0; i <= 7; i++)
    {
      // actionScore += testCaptureInDirection(GomokuReferee::directions[i], map, Action);
      
    }
  return actionScore;
}

bool			GomokuMinMax::_evaluateAction(const Map &map,
						      unsigned int &depth,
						      int &alpha,
						      int &beta,
						      GomokuMinMax::turn turn,
						      GomokuMinMax::turn nextTurn,
						      int &actionScore,
						      unsigned int i,
						      int &bestResult)
{
  Map			newMap;
  int			resultScore;
  int			result;
    
  newMap = map;
  if (turn == GomokuMinMax::MAX)
    {
      newMap.setCaseAtIndex(i, _iaColor);
      resultScore = calculateActionScore(newMap,
					 i,
					 _iaColor);
      result = _minMax(newMap, depth, alpha, beta, nextTurn, actionScore + resultScore);
      if (result > alpha)
	{
	  alpha = result;
	  bestResult = result;
	  if (alpha >= beta)
	    return false;
	}
    }
  else
    {
      newMap.setCaseAtIndex(i, _enemyColor);
      resultScore = calculateActionScore(newMap,
					 i,
					 _enemyColor);
      result = _minMax(newMap, depth, alpha, beta, nextTurn, actionScore - resultScore);
      if (result < beta)
	{
	  beta = result;
	  bestResult = result;
	  if (alpha >= beta)
	    return false;
	}
    }
  return true;
}
				       
int						GomokuMinMax::_minMax(const Map &map,
								      unsigned int depth,
								      int alpha,
								      int beta,
								      GomokuMinMax::turn turn,
								      int actionScore)
{
  Map			newMap;
  GomokuMinMax::turn	nextTurn;
  int			bestResult = 12345678;
  int			resultScore;
  
  if (turn == GomokuMinMax::MIN)
    nextTurn = GomokuMinMax::MAX;
  else
    {
      bestResult = -12345678;
      nextTurn = GomokuMinMax::MIN;
    }  
  if (depth < RECURSION_DEPTH)
    {
      ++depth;
      const std::vector<unsigned int> &pawnBoardIndexes = map.GetPawnBoardIndexes();
      int nextCaseIndex;
      for (unsigned int index: pawnBoardIndexes)
      	{
      	  // std::cout << "testing cases around case: " << index << std::endl;
      	  for (unsigned int i = 0; i < 8; i++)
      	    {
      	      nextCaseIndex = index + GomokuReferee::directions[i];
      	      if (nextCaseIndex > 0 && nextCaseIndex < MAP_SIZE)
      		{
      		  // std::cout << "    testing case : " << nextCaseIndex << std::endl;
      		  if (map.getCaseAtIndex(nextCaseIndex) == Map::EMPTY)
      		    {
      		      // std::cout << "    case available" << std::endl;
      		      if (_evaluateAction(map,
      					   depth,
      					   alpha,
      					   beta,
      					   turn,
      					   nextTurn,
      					   actionScore,
      					   nextCaseIndex,
      					   bestResult) == false)
      			{
      			  // std::cout << "    cutoff" << std::endl;
      			  return bestResult;
      			}
      		    }
      		  // std::cout << "    finished testing" << std::endl;
      		}
      	    }
      	}
      for (unsigned int i = 0; i < MAP_SIZE; i++)
      	{
      	  if (map.getCaseAtIndex(i) == Map::EMPTY)
      	    {
      	      // std::cout << "starting" << std::endl;
      	      if (_evaluateAction(map,
      				  depth,
      				  alpha,
      				  beta,
      				  turn,
      				  nextTurn,
      				  actionScore,
      				  i,
      				   bestResult) == false)
      		{
      		  // std::cout << "regular cutoff" << std::endl;
      		  return bestResult;
      		}
      	      // std::cout << "ending" << std::endl;
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
	      if (turn == GomokuMinMax::MAX)
		{
		  newMap.setCaseAtIndex(i, _iaColor);
		  resultScore = calculateActionScore(newMap,
						     i,
						     _iaColor);
		  if ((actionScore + resultScore) > alpha)
		    {
		      alpha = actionScore + resultScore;
		      bestResult = alpha;
		      if (alpha >= beta)
			return bestResult;
		    }
		}
	      else
		{
		  newMap.setCaseAtIndex(i, _enemyColor);
		  resultScore = calculateActionScore(newMap,
						     i,
						     _enemyColor);
		  if ((actionScore - resultScore) < beta)
		    {
		      beta = actionScore - resultScore;
		      bestResult = beta;
		      if (beta <= alpha)
			return bestResult;
		    }
		}
	    }
	}
    }
  return (bestResult);
}
