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
  : _iaColor(iaColor),
    _referee(_decoyMap)
{
  if (_iaColor == Map::BLACK)
    _enemyColor = Map::WHITE;
  else
    _enemyColor = Map::BLACK;
}

GomokuMinMax::GomokuMinMax()
  : _iaColor(Map::BLACK),
    _enemyColor(Map::WHITE),
    _referee(_decoyMap)
{}

Map::Coordinates	*GomokuMinMax::computeNextAction(const Map &map)
{
  GomokuMinMax::Result	result;

  result = _minMax(map, 1, -123456789, 123456789, GomokuMinMax::MAX, 0);
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
						 color), 3);
      // if (testResult == 25)
      // 	testResult = 12345678;
      actionScore += testResult;
      actionScore += pow(testAlignementInDirection(GomokuReferee::directions[i],
      						   map,
      						   Action,
      						   enemyColor), 3);
      // if (actionScore == 16)
      // 	actionScore = -12345678;
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
						      GomokuMinMax::Result &bestResult)
{
  Map			newMap;
  Map::Coordinates	nextMove;
  int			resultScore;
  GomokuMinMax::Result	result;
  IReferee::GameState	state;
    
  newMap = map;
  nextMove.x = i % MAP_WIDTH;
  nextMove.y = i / MAP_WIDTH;
  if (turn == GomokuMinMax::MAX)
    {
      newMap.setCaseAtIndex(i, _iaColor);
      // newMap.mapDump();
      _referee.setMap(newMap);
      _referee.resetReferee();
      state = _referee.validatePlayerAction(i % MAP_WIDTH,
					    i / MAP_WIDTH,
					    _iaColor);
      if (state == IReferee::GameState::P2_WIN)
	{
	  bestResult.actionScore = 12345678;
	  bestResult.coordinates.x = nextMove.x;
	  bestResult.coordinates.y = nextMove.y;
	  std::cout << "IA WINSTATE" << std::endl;
	  return false;
	}
      if (state == IReferee::GameState::ONGOING)
	{
	  resultScore = calculateActionScore(newMap,
					     nextMove,
					     _iaColor);
	  result = _minMax(newMap, depth, alpha, beta,
			   nextTurn, actionScore + resultScore);
	  if (result.actionScore > alpha)
	    {
	      alpha = result.actionScore;
	      bestResult.coordinates.x = nextMove.x;
	      bestResult.coordinates.y = nextMove.y;
	      bestResult.actionScore = result.actionScore;
	      if (alpha >= beta)
		return false;
	    }
	}
    }
  else
    {
      newMap.setCaseAtIndex(i, _enemyColor);
      // newMap.mapDump();
      _referee.setMap(newMap);
      _referee.resetReferee();
      state = _referee.validatePlayerAction(i % MAP_WIDTH,
					    i / MAP_WIDTH,
					    _enemyColor);
      if (state == IReferee::GameState::P1_WIN)
	{
	  bestResult.actionScore = -12345678;
	  bestResult.coordinates.x = nextMove.x;
	  bestResult.coordinates.y = nextMove.y;
	  std::cout << "PLAYER WINSTATE" << std::endl;
	  return false;
	}
      if (state == IReferee::GameState::ONGOING)
	{
	  resultScore = calculateActionScore(newMap,
					     nextMove,
					     _enemyColor);
	  result = _minMax(newMap, depth, alpha, beta,
			   nextTurn, actionScore - resultScore);
	  if (result.actionScore < beta)
	    {
	      beta = result.actionScore;
	      bestResult.coordinates.x = nextMove.x;
	      bestResult.coordinates.y = nextMove.y;
	      bestResult.actionScore = result.actionScore;
	      if (alpha >= beta)
		return false;
	    }
	}
    }
  return true;
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
  IReferee::GameState	state;

  if (turn == GomokuMinMax::MIN)
    nextTurn = GomokuMinMax::MAX;
  else
    {
      bestResult.actionScore = -12345678;
      nextTurn = GomokuMinMax::MIN;
    }  
  if (depth < RECURSION_DEPTH)
    {
      ++depth;
      std::vector<unsigned int> pawnBoardIndexes = map.GetPawnBoardIndexes();
      int nextCaseIndex;
      for (unsigned int index: pawnBoardIndexes)
	{
	  std::cout << "testing cases around case: " << index << std::endl;
	  for (unsigned int i = 0; i < 8; i++)
	    {
	      nextCaseIndex = index + GomokuReferee::directions[i];
	      if (nextCaseIndex > 0 && nextCaseIndex < MAP_SIZE)
		{
		  std::cout << "testing case: " << nextCaseIndex << std::endl;
		  if (map.getCaseAtIndex(nextCaseIndex) == Map::EMPTY)
		    {
		      if (!_evaluateAction(map,
					   depth,
					   alpha,
					   beta,
					   turn,
					   nextTurn,
					   actionScore,
					   nextCaseIndex,
					   bestResult))
			{
			  return bestResult;
			}
		    }
		}
	    }
	}
      for (unsigned int i = 0; i < MAP_SIZE; i++)
	{
	  if (map.getCaseAtIndex(i) == Map::EMPTY)
	    {
	      if (!_evaluateAction(map,
				   depth,
				   alpha,
				   beta,
				   turn,
				   nextTurn,
				   actionScore,
				   i,
				   bestResult))
		{
		  return bestResult;
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
		  // newMap.mapDump();
		  _referee.resetReferee();
		  _referee.setMap(newMap);
		  state = _referee.validatePlayerAction(i % MAP_WIDTH,
							i / MAP_WIDTH,
						        _iaColor);
		  if (state == IReferee::GameState::P2_WIN)
		    {
		      bestResult.actionScore = 12345678;
		      bestResult.coordinates.x = nextMove.x;
		      bestResult.coordinates.y = nextMove.y;
		      std::cout << "IA WINSTATE" << std::endl;
		      return bestResult;
		    }
		  if (state == IReferee::GameState::ONGOING)
		    {
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
		}
	      else
		{
		  newMap.setCaseAtIndex(i, _enemyColor);
		  // newMap.mapDump();
		  _referee.resetReferee();
		  _referee.setMap(newMap);
		  state = _referee.validatePlayerAction(i % MAP_WIDTH,
							i / MAP_WIDTH,
						        _enemyColor);
		  if (state == IReferee::GameState::P1_WIN)
		    {
		      bestResult.actionScore = -12345678;
		      bestResult.coordinates.x = nextMove.x;
		      bestResult.coordinates.y = nextMove.y;
		      std::cout << "PLAYER WINSTATE" << std::endl;
		      return bestResult;
		    }
		  if (state == IReferee::GameState::ONGOING)
		    {
		      resultScore = calculateActionScore(newMap,
							 nextMove,
							 _enemyColor);
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
    }
  return (bestResult);
}
