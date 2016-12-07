//
// IReferee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:17:28 2016 Thomas Billot
// Last update Tue Dec  6 13:53:14 2016 Thomas Billot
//

#ifndef			_IREFEREE_HPP_
# define		_IREFEREE_HPP_

class			IReferee
{
public:

  enum			gameState
    {
      ONGOING,
      UNVALID,
      P1_WIN,
      P2_WIN
    };

  virtual			~IReferee() {}
  virtual IReferee::gameState	validatePlayerAction(const unsigned int CoordX,
						     const unsigned int CoordY) = 0;
};

#endif			/* _IREFEREE_HPP_ */
