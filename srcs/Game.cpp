//
// Game.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Thu Dec  8 20:17:26 2016 Josselin
//

# include	<cstdio>
# include	<iostream>
# include	"Game.hpp"
# include       "GomokuReferee.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

Game::Game() : _gui(new mSFML_Window("./font/digital.otf", "Gomoku - 2016")),
	       _referee(new GomokuReferee(_map)),
	       _gomokuUI(*_gui, _map),
	       _gameHandler({{GomokuUI::Context::STARTSCREEN, &Game::_handleStartScreen},
		             {GomokuUI::Context::WAITING, &Game::_handleWaiting},
		             {GomokuUI::Context::GAME, &Game::_handleGame},
			     {GomokuUI::Context::MENU, &Game::_handleMenu}}),
	       _turn(Game::Turn::PLAYER1)
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
  IPlayer::Type				player2Type;

  if ((player2Type = _gomokuUI.displayStartScreen()) != IPlayer::Type::NONE)
    {
      _player1 = std::unique_ptr<IPlayer>(new HumanPlayer(_gomokuUI, Map::WHITE));
      if (player2Type == IPlayer::HUMAN)
	_player2 = std::unique_ptr<IPlayer>(new HumanPlayer(_gomokuUI, Map::BLACK));
      else if (player2Type == IPlayer::AI)
	_player2 = std::unique_ptr<IPlayer>(new ArtificialPlayer(new GomokuMinMax,
								 _map,
								 Map::BLACK));
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
  IReferee::gameState			gameState;
  Map::CaseState			color;
  
  try
    {
      _gomokuUI.updateMap();
      _gomokuUI.displayGame();
      std::unique_ptr<Map::Coordinates>
	newCoordinates(_turn == Game::Turn::PLAYER1 ?
		       _player1->getNextAction() : _player2->getNextAction());
      if (newCoordinates)
	{
	  gameState =_referee->validatePlayerAction(newCoordinates->x,
						    newCoordinates->y,
						    _turn);
	  switch (gameState)
	    {
	    case IReferee::gameState::ONGOING:
	      if (_turn == Game::Turn::PLAYER1)
		{
		  color = _player1->getColor();
		  _turn = Game::Turn::PLAYER2;
		}
	      else
		{
		  color = _player2->getColor();
		  _turn = Game::Turn::PLAYER1;
		}
	      _map.setCaseAt(*newCoordinates, color);
	      break;
	    case IReferee::gameState::UNVALID:
	      break;
	    case IReferee::gameState::P1_WIN:
	      break;
	    case IReferee::gameState::P2_WIN:
	      break;
	    }
	}
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      std::abort();
    }
}
