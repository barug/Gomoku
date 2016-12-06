//
// Game.hpp for Game in /home/bogard_t/rendu/tek3/Game/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Tue Dec  6 02:31:30 2016 bogard_t
//

#ifndef					__GAME_HPP__
# define				__GAME_HPP__

# include				<memory>
# include				<chrono>
# include				<map>
# include				"GomokuUI.hpp"
# include				"IReferee.hpp"

class					Game
{
public:
  Game();
  ~Game();
  int					start();

private:
  enum					Turn
    {
      PLAYER1 = 0,
      PLAYER2 = 1
    };

  Map					*_map;
  IGui					*_gui;
  IReferee				*_referee;
  Player				*_player1;
  Player				*_player2;
  GomokuUI				_gomokuUI;
  typedef void (Game::* f)(void);
  std::map<GomokuUI::Context, f>	_gameHandler;


  Game::Turn		       		_turn;

  /*
  ** private methods
  */

  void					_gameInteract();
  void				        _handleStartScreen();
  void					_handleMenu();
  void					_handleGame();
  void					_handleWaiting();

};

#endif		// __GAME_HPP__
