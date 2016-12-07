//
// Referee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:23:53 2016 Thomas Billot
// Last update Mon Dec  5 18:11:33 2016 Thomas Billot
//

#ifndef			_GOMOKUREFEREE_HPP_
# define		_GOMOKUREFEREE_HPP_

# include		"Map.hpp"
# include		"IReferee.hpp"

class			GomokuReferee : public IReferee
{
public:

  enum			Direction
    {
      NORTH,
      NORTH_EAST,
      EAST,
      SOUTH_EAST,
      SOUTH,
      SOUTH_WEST,
      WEST,
      NORTH_WEST,
    };

private:
  Map				_map;

public:
				GomokuReferee(Map &map);
  virtual			~GomokuReferee();
  virtual IReferee::gameState	validatePlayerAction(const unsigned int CoordX,
						     const unsigned int CoordY);
};

std::vector<int> testAlignement(Map &map, Map::Coordinates coordinates);

int				testAlignementInDirection(GomokuReferee::Direction direction,
							  const Map &map,
							  Map::Coordinates coordinates);
std::vector<GomokuReferee::Direction>	testCapture(Map &map, Map::Coordinates coordinates);
bool				testCaptureInDirection(GomokuReferee::Direction direction,
							       const Map &map, Map::Coordinates coordinates);


#endif			/* _GOMOKUREFEREE_HPP_ */
