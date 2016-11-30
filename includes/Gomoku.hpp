//
// Gomoku.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Wed Nov 30 15:17:49 2016 Thomas Billot
//

#ifndef		__GOMOKU_HPP__
# define	__GOMOKU_HPP__

# include	"IGui.hpp"
# include	"Case.hpp"
// # include	"IReferee.hpp"

class		Gomoku
{
  std::vector<Case*> _vecCase;
  IGui		*_gui;
  // IReferee	*_referee;

public:
  Gomoku();
  ~Gomoku();
  int		start();

private:
  /*
  ** private methods
  */

  bool	        _magnetTile(const unsigned int mouseX,
			    const unsigned int mouseY,
			    const unsigned int x,
			    const unsigned int y,
			    const unsigned int intensity = 8);
  void		_displayPlayerInfo();
  void	        _displayBackground();
  void	        _displayGameBoard();
  void		_updateMap();
  void		_checkIfClicked();

};

#endif		// __GOMOKU_HPP__
