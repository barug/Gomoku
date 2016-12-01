//
// Referee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Wed Nov 30 12:23:53 2016 Thomas Billot
// Last update Wed Nov 30 15:05:32 2016 Thomas Billot
//

#ifndef			_REFEREE_HPP_
# define		_REFEREE_HPP_

class			GomokuReferee : public IReferee
{
public:

  enum			direction
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
  
  
  Map				_map;
  
public:
				GomokuReferee();
  virtual			~GomokuReferee();
  virtual IReferee::gameState	validatePlayerAction(const unsigned int &CoordX,
						     const unsigned int &CoordY);
};

bool				testAlignement(gomokuReferee::direction direction,
					       const Map &map);
bool				testCapture(gomokuReferee::direction direction,
					    const Map &map);


#endif			/* _REFEREE_HPP_ */
