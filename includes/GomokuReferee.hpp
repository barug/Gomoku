//
// Referee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:23:53 2016 Thomas Billot
// Last update Tue Dec  6 11:31:16 2016 Thomas Billot
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
      NORTH		= -19,
      NORTH_EAST	= -18,
      EAST		= 1,
      SOUTH_EAST	= 20,
      SOUTH		= 19,
      SOUTH_WEST	= 18,
      WEST		= -1,
      NORTH_WEST	= -20,
    };

   static constexpr GomokuReferee::Direction directions[8] = {NORTH,
							      NORTH_EAST,
							      EAST,
							      SOUTH_EAST,
							      SOUTH,
							      SOUTH_WEST,
							      WEST,
							      NORTH_WEST};
  
private:
  Map				_map;

public:
  explicit 			GomokuReferee(Map &map);
  virtual			~GomokuReferee();
  virtual IReferee::gameState	validatePlayerAction(const unsigned int CoordX,
						     const unsigned int CoordY);
};

std::vector<int>	testAlignement(Map &map, Map::Coordinates coordinates);

int			testAlignementInDirection(GomokuReferee::Direction direction,
						  const Map &map,
						  Map::Coordinates coordinates,
						  Map::CaseState color);
std::vector<GomokuReferee::Direction>	testCapture(Map &map,
						    Map::Coordinates coordinates);
bool			testCaptureInDirection(GomokuReferee::Direction direction,
					       const Map &map,
					       Map::Coordinates coordinates);


#endif			/* _GOMOKUREFEREE_HPP_ */
