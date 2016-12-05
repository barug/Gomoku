//
// Game.hpp for Game in /home/bogard_t/rendu/tek3/Game/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Mon Dec  5 15:44:29 2016 bogard_t
//

#ifndef		__GAME_HPP__
# define	__GAME_HPP__

# include	<memory>
# include	<chrono>
# include	<map>
# include	"IGui.hpp"
# include	"IReferee.hpp"
# include	"Map.hpp"
# include	"Player.hpp"
# include	"TimerContext.hpp"

class		Game
{
public:
  Game();
  ~Game();

  int		start();

private:
  enum		Context
    {
      STARTSCREEN = 0,
      WAITING = 1,
      GAME = 2,
      MENU = 3
    };

  enum		Turn
    {
      PLAYER1 = 0,
      PLAYER2
    };

  IGui		*_gui;
  IReferee	*_referee;
  Map		*_map;
  Game::Context _context;
  Game::Turn	_turn;
  TimerContext	_menuTimerContext;
  TimerContext	_waitingTimerContext;
  TimerContext	_clickTimerContext;
  Player	_player1;
  Player	_player2;
  std::map<Game::Context, void (Game::*)(void)>	_gameHandler;
  std::chrono::system_clock::time_point _lastTick;
  std::chrono::system_clock::time_point _lastClick;
  std::chrono::system_clock::time_point	_now;

  /*
  ** private methods
  */

  static const int	timerWaiting = 700;
  static const int	timerMenu = 200;
  static const int	timerClick = 200;

  bool	        _magnetTile(const unsigned int mouseX,
			    const unsigned int mouseY,
			    const unsigned int x,
			    const unsigned int y,
			    const unsigned int intensityX = 13,
			    const unsigned int intensityY = 13) const;

  void		_displayPlayerInfo() const;
  void	        _displayInGameBackground() const;
  void	        _displayGameBoard() const;
  void		_updateMap();
  void		_gameInteract();
  void	        _handleStartScreen();
  void		_handleMenu();
  void		_handleGame();
  void		_handleWaiting();
  void		_resetToFirstScreen();

};

#endif		// __GAME_HPP__
