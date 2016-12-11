//
// Game.cpp for Gomoku
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Sat Dec 10 19:34:35 2016 bogard_t
//

# include	<cstdio>
# include	<iostream>
# include	"Game.hpp"
# include       "GomokuReferee.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

Game::Game() : _gui(new mSFML_Window("./font/digital.otf", "Gomoku - 2016")),
               _audio(new mSFML_Audio),
	       _referee(new GomokuReferee(_map)),
	       _gomokuUI(*_gui, _map),
	       _gameHandler({{GomokuUI::Context::START_SCREEN, &Game::_handleStartScreen},
			     {GomokuUI::Context::WAITING, &Game::_handleWaiting},
			     {GomokuUI::Context::GAME, &Game::_handleGame},
			     {GomokuUI::Context::WIN_SCREEN, &Game::_handleWinScreen},
			     {GomokuUI::Context::MENU, &Game::_handleMenu}}),
	       _turn(Game::Turn::PLAYER1)
{
  _audio->loadSound("./sound/signal.wav");
  _audio->soundSetVolume(10);
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

  _referee->resetReferee();
  if ((player2Type = _gomokuUI.displayStartScreen()) != IPlayer::Type::NONE)
    {
      _player1 = std::unique_ptr<IPlayer>(new HumanPlayer(_gomokuUI, Map::WHITE));
      if (player2Type == IPlayer::HUMAN)
        {
          _player2 = std::unique_ptr<IPlayer>(new HumanPlayer(_gomokuUI, Map::BLACK));
        }
      else if (player2Type == IPlayer::AI)
        {
          _player2 = std::unique_ptr<IPlayer>
            (new ArtificialPlayer(new GomokuMinMax(Map::BLACK), _map, Map::BLACK));
        }
      _gomokuUI.setContext(GomokuUI::Context::WAITING);
    }
}

void					Game::_handleWaiting()
{
  _gomokuUI.displayWaiting();
}

void					Game::_handleMenu()
{
  _gomokuUI.displayUI(_player1->getScore(), _player2->getScore(),
		      _referee->getP1Score(), _referee->getP2Score());
  _gomokuUI.updateMap();
  _gomokuUI.displayMenu();
}

void					Game::_handleWinScreen()
{
  _gomokuUI.displayUI(_player1->getScore(), _player2->getScore(),
  		      _referee->getP1Score(), _referee->getP2Score());
  _gomokuUI.updateMap();
  if (_gameState == IReferee::GameState::P1_WIN)
    _gomokuUI.displayWinScreen("PLAYER 1 WIN");
  else if (_gameState == IReferee::GameState::P2_WIN and _player2->getType() != IPlayer::AI)
    _gomokuUI.displayWinScreen("PLAYER 2 WIN");
  else
    _gomokuUI.displayWinScreen("YOU LOOSE VS AI, YOU SUCH A DUMB!");
}

void					Game::_handleGame()
{
  try
    {
      _gomokuUI.displayUI(_player1->getScore(), _player2->getScore(),
 			  _referee->getP1Score(), _referee->getP2Score());
      _gomokuUI.updateMap();
      _gomokuUI.displayGame();

      std::unique_ptr<Map::Coordinates>
	newCoordinates(_turn == Game::Turn::PLAYER1 ?
		       _player1->getNextAction() : _player2->getNextAction());

      if (newCoordinates)
	{
	  std::cout << newCoordinates->x << " " << newCoordinates->y << std::endl;
	  _gameState =_referee->validatePlayerAction(newCoordinates->x,
						     newCoordinates->y,
						     _turn);
	  switch (_gameState)
	    {
	    case IReferee::GameState::ONGOING:
              _audio->soundPlay();
	      _turn = (_turn == Game::Turn::PLAYER1 ? Game::Turn::PLAYER2 : Game::Turn::PLAYER1);
	      break;
	    case IReferee::GameState::UNVALID:
	      break;
	    case IReferee::GameState::P1_WIN:
              _turn = Game::Turn::PLAYER1;
	      _player1->setScore(_player1->getScore() + 1);
	      _gomokuUI.setContext(GomokuUI::Context::WIN_SCREEN);
	      break;
	    case IReferee::GameState::P2_WIN:
              _turn = Game::Turn::PLAYER1;
	      _player2->setScore(_player2->getScore() + 1);
	      _gomokuUI.setContext(GomokuUI::Context::WIN_SCREEN);
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
