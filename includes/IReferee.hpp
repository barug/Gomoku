//
// IReferee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:17:28 2016 Thomas Billot
// Last update Thu Dec  1 01:30:03 2016 bogard_t
//

#ifndef			_IREFEREE_HPP_
# define		_IREFEREE_HPP_

class			IReferee
{

public:

  virtual		~IReferee() {}
  virtual void	        onClick(const unsigned int CoordX, const unsigned int CoordY) = 0;
};

#endif			/* _IREFEREE_HPP_ */
