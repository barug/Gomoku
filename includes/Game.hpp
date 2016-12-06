//
// Game.hpp for Game in /home/bogard_t/rendu/tek3/Game/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Tue Dec  6 14:11:25 2016 bogard_t
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

  typedef void (Game::* f)(void);

  std::unique_ptr<Map>			_map;
  std::unique_ptr<IGui>		        _gui;
  std::unique_ptr<IReferee>	        _referee;
  std::unique_ptr<Player>	        _player1;
  std::unique_ptr<Player>	        _player2;

  GomokuUI				_gomokuUI;

  std::map<GomokuUI::Context, f>	_gameHandler;

  Game::Turn		       		_turn;

  /*
  ** private methods handler
  */

  void				        _handleStartScreen();
  void					_handleMenu();
  void					_handleGame();
  void					_handleWaiting();

};

#endif		// __GAME_HPP__
