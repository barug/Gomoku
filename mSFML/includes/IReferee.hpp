//
// IReferee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Wed Nov 30 12:17:28 2016 Thomas Billot
// Last update Wed Nov 30 12:33:32 2016 Thomas Billot
//

#ifndef			_IREFEREE_HPP_
# define		_IREFEREE_HPP_

# include		"IWindow.hpp"

class			IReferee
{

public:

  virtual		~IReferee() {}
  virtual void	        onClick(const unsigned int CoordX, const unsigned int CoordY) = 0;
};

#endif			/* _IREFEREE_HPP_ */
