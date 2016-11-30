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

class			Referee : public IReferee
{

  Map			_map;
  
public:

  Referee();
  ~Referee();
  void			OnTileAt(const unsigned int &CoordX, const unsigned int &CoordY);
};

#endif			/* _REFEREE_HPP_ */
