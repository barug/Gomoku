//
// BoardGame.hpp for BoardGame in /home/bogard_t/rendu/tek3/BoardGame/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Thu Dec  1 17:14:03 2016 bogard_t
//

#ifndef		__BOARD_GAME_HPP__
# define	__BOARD_GAME_HPP__

# include	"IGui.hpp"
# include	"IReferee.hpp"
# include	"Map.hpp"
# include	<memory>

class		BoardGame
{
  enum		Context
    {
      STARTSCREEN = 0,
      GAME = 1,
      MENU = 2
    };

  IGui		*_gui;
  IReferee	*_referee;
  Map		*_map;
  BoardGame::Context _context;

public:
  BoardGame();
  ~BoardGame();

  int		start();

private:

  /*
  ** private methods
  */

  bool	        _magnetTileCircle(const unsigned int mouseX,
				  const unsigned int mouseY,
				  const unsigned int x,
				  const unsigned int y,
				  const unsigned int intensityX = 13,
				  const unsigned int intensityY = 13) const;

  void	        _displayStartScreen();
  void		_displayPlayerInfo() const;
  void	        _displayInGameBackground() const;
  void	        _displayGameBoard() const;
  void		_updateMap();
  void		_gameInteract();

};

#endif		// __BOARD_GAME_HPP__
