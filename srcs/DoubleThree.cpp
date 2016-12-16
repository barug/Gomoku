/*
** Tests Double Tois
*/
bool			GomokuReferee::testSimpleThreePattern(Map::Coordinates coordinates, int xInc, int yInc, int xBack, int yBack) /* Xxx */
{
  if (countAlignement(coordinates, xInc, yInc) == 3)
    {
      while (coordinates.x + xInc >= 0 && coordinates.x + xInc <= 19 &&
	     coordinates.y + yInc >= 0 && coordinates.y + yInc <= 19 &&
	     this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
	     this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)))
	{
	  xInc = xInc < 0 ? xInc - 1 : xInc > 0 ? xInc + 1 : 0;
	  yInc = yInc < 0 ? yInc - 1 : yInc > 0 ? yInc + 1 : 0;
	}

      if (coordinates.y + yBack >= 0 && coordinates.y + yBack <= 19 &&
	  coordinates.x + xBack >= 0 && coordinates.x + xBack <= 19 &&
	  this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yBack) + (coordinates.x + xBack)) == Map::CaseState::EMPTY &&
	  this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)) == Map::CaseState::EMPTY)
	return true;
    }
  return false;
}

bool			GomokuReferee::testSpacePattern(Map::Coordinates coordinates, int xInc, int yInc, int xBack, int yBack) /* X*xx */
{
  if (coordinates.y + (yInc * 4) >= 0 && coordinates.y + (yInc * 4) <= 19 &&
      coordinates.x + (xInc * 4) >= 0 && coordinates.x + (xInc * 4) <= 19 &&
      coordinates.y + yBack >= 0 && coordinates.y + yBack <= 19 &&
      coordinates.x + xBack >= 0 && coordinates.x + xBack <= 19 &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)) == Map::CaseState::EMPTY &&
      this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2))) &&
      this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))) &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 4)) + (coordinates.x + (xInc * 4))) == Map::CaseState::EMPTY &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yBack) + (coordinates.x + xBack)) == Map::CaseState::EMPTY)
    return true;
  return false;
}

bool			GomokuReferee::testInvertSpacePattern(Map::Coordinates coordinates, int xInc, int yInc, int xBack, int yBack) /* Xx*x */
{
  if (coordinates.y + (yInc * 4) >= 0 && coordinates.y + (yInc * 4) <= 19 &&
      coordinates.x + (xInc * 4) >= 0 && coordinates.x + (xInc * 4) <= 19 &&
      coordinates.y + yBack >= 0 && coordinates.y + yBack <= 19 &&
      coordinates.x + xBack >= 0 && coordinates.x + xBack <= 19 &&
      this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) == this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yInc) + (coordinates.x + xInc)) &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 2)) + (coordinates.x + (xInc * 2))) == Map::CaseState::EMPTY &&
      this->_map.getCaseAtIndex(MAP_WIDTH * coordinates.y + coordinates.x) ==
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 3)) + (coordinates.x + (xInc * 3))) &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + (yInc * 4)) + (coordinates.x + (xInc * 4))) == Map::CaseState::EMPTY &&
      this->_map.getCaseAtIndex(MAP_WIDTH * (coordinates.y + yBack) + (coordinates.x + xBack)) == Map::CaseState::EMPTY)
    return true;
  return false;
}


bool			GomokuReferee::testDoubleThree(Map::Coordinates coordinates)
{
  int			count = 0;
  int			xBack;
  int			yBack;

  for (int xInc = -1; xInc < 2; xInc++)
    {
      for (int yInc = -1; yInc < 2; yInc++)
	{
	  if (xInc == 0 && yInc == 0);
	  else
	    {
	      xBack = xInc == 0 ? 0 : xInc == -1 ? 1 : xInc == 1 ? -1 : 0;
	      yBack = yInc == 0 ? 0 : yInc == -1 ? 1 : yInc == 1 ? -1 : 0;

	      if (testSimpleThreePattern(coordinates, xInc, yInc, xBack, yBack) ||
		  testSpacePattern(coordinates, xInc, yInc, xBack, yBack) ||
		  testInvertSpacePattern(coordinates, xInc, yInc, xBack, yBack))
	      if (++count == 2)
		return true;
	    }
	}
    }
  return false;
}
