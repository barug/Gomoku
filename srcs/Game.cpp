//
// Game.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Tue Dec  6 15:08:19 2016 Thomas Billot
//

# include	<cstdio>
# include	<iostream>
# include	"Game.hpp"
# include       "GomokuReferee.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

Game::Game() : _map(new Map),
	       _gui(new mSFML_Window("./font/digital.otf", "Gomoku - 2016")),
	       _referee(new GomokuReferee(*_map)),
	       _player1(new Player),
	       _player2(new Player),
	       _gomokuUI(*_gui, *_map),
	       _gameHandler({{GomokuUI::Context::STARTSCREEN,	&Game::_handleStartScreen},
			     {GomokuUI::Context::WAITING,	&Game::_handleWaiting},
			     {GomokuUI::Context::GAME,		&Game::_handleGame},
			     {GomokuUI::Context::MENU,		&Game::_handleMenu}})
{
}

Game::~Game()
{
}

int					Game::start()
{
  while (_gui->isAlive())
    {
      _gui->clear();
      _gui->handleEvents();
      ((*this).*(_gameHandler[_gomokuUI.getContext()]))();
      _gui->display();
    }
  return 0;
}

void					Game::_handleStartScreen()
{
  _gomokuUI.displayStartScreen(*_player2);
}

void					Game::_handleWaiting()
{
  _gomokuUI.displayWaiting();
}

void					Game::_handleMenu()
{
  _gomokuUI.updateMap();
  _gomokuUI.displayMenu();
}

void					Game::_handleGame()
{
  try
    {
      _gomokuUI.updateMap();
      _gomokuUI.displayGame();
      std::unique_ptr<Map::Coordinates>	newCoordinates(_gomokuUI.getClickedTile());

      if (newCoordinates)
	{
	  switch (_turn)
	    {
	    case Game::Turn::PLAYER1:
	      if (_referee->validatePlayerAction(newCoordinates->getX(), newCoordinates->getY())
		  == IReferee::gameState::ONGOING)
		_map->setCaseAt(*newCoordinates, Map::CaseState::WHITE);
	      else
		std::cout << "PLAYER1 wiiiiiinn" << std::endl;
	      break;
	    case Game::Turn::PLAYER2:
	      if (_player2->getType() == Player::Type::AI)
		std::cout << "player 2 is AI" << std::endl;
	      if (_referee->validatePlayerAction(newCoordinates->getX(), newCoordinates->getY())
		  == IReferee::gameState::ONGOING)
		_map->setCaseAt(*newCoordinates, Map::CaseState::BLACK);
	      else
		std::cout << "PLAYER1 wiiiiiinn" << std::endl;
	      break;
	    default:
	      break;
	    }
	  _turn = _turn == Game::Turn::PLAYER1 ? Game::Turn::PLAYER2 : Game::Turn::PLAYER1;

	}
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      std::abort();
    }
}
