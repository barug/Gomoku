//
// Game.hpp for Game in /home/bogard_t/rendu/tek3/Game/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Mon Dec  5 23:20:22 2016 bogard_t
//

#ifndef		__GAME_HPP__
# define	__GAME_HPP__

# include	<memory>
# include	<chrono>
# include	<map>
# include	"GomokuUI.hpp"
# include	"IReferee.hpp"

class		Game
{
public:
  Game();
  ~Game();
  int		start();

private:
  enum		Turn
    {
      PLAYER1 = 0,
      PLAYER2
    };

  Map		*_map;
  IGui		*_gui;
  IReferee	*_referee;

  std::map<GomokuUI::Context, void (Game::*)(void)>	_gameHandler;

  Game::Turn	_turn;
  GomokuUI	_gomokuUI;

  Player	_player1;
  Player	_player2;

  /*
  ** private methods
  */

  void		_gameInteract();
  void	        _handleStartScreen();
  void		_handleMenu();
  void		_handleGame();
  void		_handleWaiting();

};

#endif		// __GAME_HPP__
