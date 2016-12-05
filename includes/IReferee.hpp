//
// IReferee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:17:28 2016 Thomas Billot
// Last update Fri Dec  2 18:22:04 2016 Josselin
//

#ifndef			_IREFEREE_HPP_
# define		_IREFEREE_HPP_

class			IReferee
{
public:

  enum			gameState
    {
      ONGOING,
      P1_WIN,
      P2_WIN
    };

				IReferee() {}
  virtual			~IReferee() {}
  virtual IReferee::gameState	validatePlayerAction(const unsigned int CoordX,
						     const unsigned int CoordY) = 0;
};

#endif			/* _IREFEREE_HPP_ */
