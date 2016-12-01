//
// Gomoku.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Thu Dec  1 02:11:47 2016 bogard_t
//

#ifndef		__GOMOKU_HPP__
# define	__GOMOKU_HPP__

# include	"IGui.hpp"
# include	"IReferee.hpp"
# include	"map.hpp"
# include	<memory>

class		Gomoku
{
  IGui		*_gui;
  IReferee	*_referee;
  Map		*_map;

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
			    const unsigned int intensity = 13) const;
  void		_displayPlayerInfo() const;
  void	        _displayBackground() const;
  void	        _displayGameBoard() const;
  void		_updateMap();
  void		_checkIfClicked();

};

#endif		// __GOMOKU_HPP__
