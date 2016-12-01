//
// BoardGame.hpp for BoardGame in /home/bogard_t/rendu/tek3/BoardGame/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Thu Dec  1 14:13:49 2016 bogard_t
//

#ifndef		__BOARD_GAME_HPP__
# define	__BOARD_GAME_HPP__

# include	"IGui.hpp"
# include	"IReferee.hpp"
# include	"Map.hpp"
# include	<memory>

class		BoardGame
{
  IGui		*_gui;
  IReferee	*_referee;
  Map		*_map;

public:
  BoardGame();
  ~BoardGame();

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

#endif		// __BOARD_GAME_HPP__
