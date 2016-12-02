//
// BoardGame.hpp for BoardGame in /home/bogard_t/rendu/tek3/BoardGame/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Fri Dec  2 01:37:23 2016 bogard_t
//

#ifndef		__BOARD_GAME_HPP__
# define	__BOARD_GAME_HPP__

# include	<memory>
# include	<chrono>
# include	"IGui.hpp"
# include	"IReferee.hpp"
# include	"Map.hpp"

# define	TICK_DURATION (500)

class		BoardGame
{
  enum		Context
    {
      STARTSCREEN = 0,
      WAITING = 1,
      GAME = 2,
      MENU = 3
    };

  IGui		*_gui;
  IReferee	*_referee;
  Map		*_map;
  BoardGame::Context _context;
  std::chrono::system_clock::time_point _lastTick;
  std::chrono::system_clock::time_point	_now;
  bool		_timerFirstToSecondScreen;

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
  void	        _displayWaiting() const;
  void	        _displayMenu() const;
  void		_updateMap();
  void		_gameInteract();

};

#endif		// __BOARD_GAME_HPP__
