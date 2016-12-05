//
// Game.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Mon Dec  5 22:09:02 2016 bogard_t
//

# include	<cstdio>
# include	<iostream>
# include	"Game.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

Game::Game() : _map(new Map),
	       _gui(new mSFML_Window("./font/digital.otf", "Gomoku - 2016")),
	       _gomokuUI(*_gui, *_map),
	       _turn(Turn::PLAYER1),
	       _gameHandler({{GomokuUI::Context::STARTSCREEN, &Game::_handleStartScreen},
	       	     {GomokuUI::Context::WAITING, &Game::_handleWaiting},
	       	       {GomokuUI::Context::GAME, &Game::_handleGame},
	       		 {GomokuUI::Context::MENU, &Game::_handleMenu}})
{
  for (auto x = 0; x < IGui::mapSize; x++)
    for (auto y = 0; y < IGui::mapSize; y++)
      _map->setCaseAt(Map::Coordinates(x, y), Map::CaseState::EMPTY);
}

Game::~Game()
{
}

int		Game::start()
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

void		Game::_handleStartScreen()
{
  _gomokuUI.displayStartScreen();
}

  void		Game::_handleWaiting()
{
  _gomokuUI.displayWaiting();
}

void		Game::_handleMenu()
{
  _gomokuUI.updateMap();
  _gomokuUI.displayMenu();
}

void		Game::_handleGame()
{
  std::unique_ptr<Map::Coordinates> newCoordinates(_gomokuUI.getClickedOnTile());

  _gomokuUI.updateMap();
  if (newCoordinates)
    {
      switch (_turn)
	{
	case Game::Turn::PLAYER1:
	  {
	    // if arbiter allow
	    _map->setCaseAt(*newCoordinates, Map::CaseState::WHITE);


	  }
	  break;
	case Game::Turn::PLAYER2:
	  {
	    // if arbiter allow
	    _map->setCaseAt(*newCoordinates, Map::CaseState::BLACK);


	  }
	  break;
	default:
	  break;
	}
      _turn = _turn == Game::Turn::PLAYER1 ? Game::Turn::PLAYER2 : Game::Turn::PLAYER1;
    }
}
