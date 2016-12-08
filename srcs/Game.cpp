//
// Game.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Thu Dec  8 17:49:13 2016 bogard_t
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
  Player::Type				getType;

  if ((getType = _gomokuUI.displayStartScreen()) != Player::Type::NONE)
    {
      _player1->setType(Player::Type::HUMAN);
      _player2->setType(getType);
      _gomokuUI.setContext(GomokuUI::Context::WAITING);
    }
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
	  Map::CaseState			caseState;
	  IReferee::gameState			state =_referee->
	    validatePlayerAction(newCoordinates->x, newCoordinates->y);

	  switch (state)
	    {

	    case IReferee::gameState::ONGOING:
	      _turn = (_turn == Game::Turn::PLAYER1 ? Game::Turn::PLAYER2 : Game::Turn::PLAYER1);
	      caseState = (_turn == Game::Turn::PLAYER1 ? Map::CaseState::WHITE : Map::CaseState::BLACK);
	      break;

	    case IReferee::gameState::UNVALID:
	      _turn = (_turn == Game::Turn::PLAYER1 ? Game::Turn::PLAYER1 : Game::Turn::PLAYER2);
	      caseState = Map::CaseState::EMPTY;
	      break;

	    default:
	      caseState = Map::CaseState::EMPTY;
	      break;
	    }
	  _map->setCaseAt(*newCoordinates, caseState);
	}
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      std::abort();
    }
}
