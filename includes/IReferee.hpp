//
// IReferee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:17:28 2016 Thomas Billot
// Last update Sat Dec 10 19:21:11 2016 bogard_t
//

#ifndef			_IREFEREE_HPP_
# define		_IREFEREE_HPP_

class			IReferee
{
public:

  enum			GameState
    {
      ONGOING,
      UNVALID,
      P1_WIN,
      P2_WIN
    };

  virtual			~IReferee() {}
  virtual IReferee::GameState	validatePlayerAction(int CoordX, int CoordY, const bool turn) = 0;
  virtual void			resetReferee() = 0;
  virtual int			getP1Score() = 0;
  virtual int			getP2Score() = 0;
  virtual void			reset() = 0;
};

#endif			/* _IREFEREE_HPP_ */
