//
// Game.hpp for Game in /home/bogard_t/rendu/tek3/Game/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:17:52 2016 bogard_t
// Last update Sat Dec 10 18:29:11 2016 bogard_t
//

#ifndef					__GAME_HPP__
# define				__GAME_HPP__

# include				<map>
# include				<memory>
# include				<chrono>
# include				"GomokuUI.hpp"
# include				"IReferee.hpp"
# include				"IPlayer.hpp"
# include				"HumanPlayer.hpp"
# include				"ArtificialPlayer.hpp"
# include				"MinMax.hpp"

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

  Map					_map;
  std::shared_ptr<IGui>		        _gui;
  std::unique_ptr<IReferee>	        _referee;
  std::unique_ptr<IPlayer>	        _player1;
  std::unique_ptr<IPlayer>	        _player2;

  GomokuUI				_gomokuUI;

  std::map<GomokuUI::Context, f>	_gameHandler;

  Game::Turn		       		_turn;
  IReferee::GameState			_gameState;

  /*
  ** private methods
  */

  void				        _handleStartScreen();
  void					_handleMenu();
  void					_handleGame();
  void					_handleWaiting();
  void				        _handleWinScreen();

};

#endif		// __GAME_HPP__
