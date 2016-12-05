//
// Game.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Mon Dec  5 16:35:39 2016 Thomas Billot
//

# include	<cstdio>
# include	<iostream>
# include	"Game.hpp"
# include       "GomokuReferee.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

Game::Game() : _gui(new mSFML_Window("./font/digital.otf", "Gomoku - 2016")),
	       _referee(new GomokuReferee()),
	       _map(new Map),
	       _context(Context::STARTSCREEN),
	       _turn(Turn::PLAYER1),
	       _gameHandler({{Game::Context::STARTSCREEN, &Game::_handleStartScreen},
	       	     {Game::Context::WAITING, &Game::_handleWaiting},
	       	       {Game::Context::GAME, &Game::_handleGame},
	       		 {Game::Context::MENU, &Game::_handleMenu}})
{
  for (unsigned int x = 0; x < IGui::mapSize; x++)
    for (unsigned int y = 0; y < IGui::mapSize; y++)
      _map->setCaseAt(Map::Coordinates(x, y), Map::CaseState::EMPTY);
}

Game::~Game()
{
  delete _gui;
  delete _map;
}

int		Game::start()
{
  while (_gui->isAlive())
    {
      _gui->clear();
      _gui->handleEvents();
      ((*this).*(_gameHandler[_context]))();
      _gui->display();
    }
  return 0;
}

bool		Game::_magnetTile(const unsigned int mouseX,
				  const unsigned int mouseY,
				  const unsigned int x,
				  const unsigned int y,
				  const unsigned int intensityX,
				  const unsigned int intensityY) const
{
  for (unsigned int i = 0; i < intensityX; i++)
    for (unsigned int j = 0; j < intensityY; j++)
      if ((mouseX + i == x && mouseY + i == y) ||
	  (mouseX + i == x && mouseY + j == y) ||
	  (mouseX + j == x && mouseY + j == y) ||
	  (mouseX + j == x && mouseY + i == y) ||

	  (mouseX + i == x && mouseY - i == y) ||
	  (mouseX + i == x && mouseY - j == y) ||
	  (mouseX + j == x && mouseY - j == y) ||
	  (mouseX + j == x && mouseY - i == y) ||

	  (mouseX - i == x && mouseY + i == y) ||
	  (mouseX - i == x && mouseY + j == y) ||
	  (mouseX - j == x && mouseY + j == y) ||
	  (mouseX - j == x && mouseY + i == y) ||

	  (mouseX - i == x && mouseY - i == y) ||
	  (mouseX - i == x && mouseY - j == y) ||
	  (mouseX - j == x && mouseY - j == y) ||
	  (mouseX - j == x && mouseY - i == y))
	return (true);
  return (false);
}

void		Game::_displayPlayerInfo() const
{
  _gui->writeAt("SCORE J1 :", 40, 50, 0xffffff, 0.5);
  _gui->fillRec(40, 70, 60, 1, 0xffffff);
  _gui->writeAt("PIONS RESTANTS :", 40, 100, 0xffffff, 0.5);
  _gui->fillRec(40, 120, 100, 1, 0xffffff);
  _gui->writeAt("ALIGNEMENT :", 40, 150, 0xffffff, 0.5);
  _gui->fillRec(40, 170, 75, 1, 0xffffff);
  _gui->writeAt("SCORE J2 :", 40, 350, 0xffffff, 0.5);
  _gui->fillRec(40, 370, 60, 1, 0xffffff);
  _gui->writeAt("PIONS RESTANTS :", 40, 400, 0xffffff, 0.5);
  _gui->fillRec(40, 420, 100, 1, 0xffffff);
  _gui->writeAt("ALIGNEMENT :", 40, 450, 0xffffff, 0.5);
  _gui->fillRec(40, 470, 75, 1, 0xffffff);
}

void		Game::_displayInGameBackground() const
{
  _gui->fillRec(0, 0, 800, 600, 0xffffff);
  _gui->fillRec(0, 0, 190, 600, 0x000000);
  _gui->fillRec(0, 300, 200, 10, 0xffffff);
  _gui->setTextureAt("./sprites/wood.jpg", 200, 0, 1.);
  _gui->fillRec(0, 0, 800, 10, 0xffffff);
  _gui->fillRec(0, 590, 800, 10, 0xffffff);
  _gui->fillRec(790, 0, 10, 800, 0xffffff);
  _gui->fillRec(0, 0, 10, 600, 0xffffff);
}

void		Game::_displayGameBoard() const
{
  for (unsigned int x = 0; x < IGui::mapSize - 1; x++)
    {
      for (unsigned int y = 0; y < IGui::mapSize - 1; y++)
	{
	  _gui->fillRec(IGui::offsetMapX + (x * IGui::offsetX),
			IGui::offsetMapY + (y * IGui::offsetY), 30, 2, 0x000000);
	  _gui->fillRec(IGui::offsetMapX + (x * IGui::offsetX),
			IGui::offsetMapY + (y * IGui::offsetY), 2, 30, 0x000000);
	}
    }
  _gui->fillRec(IGui::offsetMapX + ((IGui::mapSize - 1) * IGui::offsetX),
		IGui::offsetMapY + (0 * IGui::offsetY),
		2, (IGui::offsetY * (IGui::mapSize - 1)) + 2, 0x000000);

  _gui->fillRec(IGui::offsetMapX + (0 * IGui::offsetX),
		IGui::offsetMapY + ((IGui::mapSize - 1) * IGui::offsetY),
		(IGui::offsetX * (IGui::mapSize - 1)) + 1, 2, 0x000000);
}

void		Game::_updateMap()
{
  for (unsigned int i = 0; i < _map->getMapData().size(); i++)
    {
      if (_map->getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	  == Map::CaseState::WHITE)
	{
	  _gui->setTextureAt("./sprites/white.png",
			     IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
			     IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1);
	}
      else if (_map->getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	       == Map::CaseState::BLACK)
	{
	  _gui->setTextureAt("./sprites/black.png",
			     IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
			     IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1);
	}
      if (_context == Context::GAME)
	if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(),
			      IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetY),
			      IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetX)))
	  {
	    (_map->getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	     == Map::CaseState::EMPTY) ?
	      _gui->setTextureAt("./sprites/cercle_vert.png",
				 IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
				 IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1) :
	      _gui->setTextureAt("./sprites/cercle_rouge.png",
	      			 IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
	      			 IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1);
	  }
    }
}

// handler
void		Game::_handleStartScreen()
{
  _gui->setTextureAt("./sprites/background.jpg", 0, 0, 0.5);
  _gui->setTextureAt("./sprites/gomoku.png", 130, 100, 0.4);
  _gui->writeAt("project for tek3 by : barthe_g, billot_t, bloy_j, bogard_t",
		230, 560, 0xffffff, 0.5);
  if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(),
  			400, 340, 40, 40))
    {
      if (_gui->buttonLeftIsClicked())
	_context = Context::WAITING;
      _gui->fillRec(300, 300, 200, 80, 0x000000, 180);
      _gui->writeAt("Player vs Player", 315, 325, 0x00ff00, 0.8);
    }
  else
    {
      _gui->fillRec(300, 300, 200, 80, 0xffffff, 180);
      _gui->writeAt("Player vs Player", 315, 325, 0x000000, 0.8);
    }
  if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(),
  			400, 440, 40, 40))
    {
      if (_gui->buttonLeftIsClicked())
	{
	  _context = Context::WAITING;
	  _player2 = Player::Type::AI;
	}
      _gui->fillRec(300, 400, 200, 80, 0x000000, 180);
      _gui->writeAt("Player vs AI", 340, 425, 0x00ff00, 0.8);
    }
  else
    {
      _gui->fillRec(300, 400, 200, 80, 0xffffff, 180);
      _gui->writeAt("Player vs AI", 340, 425, 0x000000, 0.8);
    }
}

void		Game::_resetToFirstScreen()
{
  _context = Context::STARTSCREEN;
  _waitingTimerContext.setState(TimerContext::State::NONE);
  _menuTimerContext.setState(TimerContext::State::NONE);
  _turn = Game::Turn::PLAYER1;
  for (unsigned int x = 0; x < IGui::mapSize; x++)
    for (unsigned int y = 0; y < IGui::mapSize; y++)
      _map->setCaseAt(Map::Coordinates(x, y), Map::CaseState::EMPTY);
}

void		Game::_handleMenu()
{
  if (_menuTimerContext.getState() == TimerContext::State::TIMER_OUT
      && _gui->getKey() == IGui::SPACE)
    {
      _context = Context::GAME;
      _menuTimerContext.setState(TimerContext::State::PUSHED);
    }
  _displayInGameBackground();
  _displayGameBoard();
  _updateMap();
  _displayPlayerInfo();
  _gui->fillRec(0, 0, 800, 600, 0x000000, 180);
  _gui->writeAt("MENU", 400, 70, 0x00ff00, 1.2);
  _gui->fillRec(390, 115, 100, 2, 0x00ff00);
  _gui->writeAt("BACK TO HOME", 330, 370, 0x00ff00, 1.2);

  // reset firstscreen
  if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(), 410, 370, 50, 30))
    if (_gui->buttonLeftIsClicked())
      _resetToFirstScreen();

  _now = std::chrono::system_clock::now();
  if (_menuTimerContext.getState() == TimerContext::State::PUSHED)
    {
      std::cout << "[TIMER::MENU] reinit" << std::endl;
      _lastTick = std::chrono::system_clock::now();
      _menuTimerContext.setState(TimerContext::State::TIMER_IN);
    }
  if (_menuTimerContext.getState() == TimerContext::State::TIMER_IN)
    {
      if (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastTick).count()
	  > timerMenu)
	{
	  std::cout << "[TIMER::MENU] is finished" << std::endl;
	  _lastTick = _now;
	  _menuTimerContext.setState(TimerContext::State::TIMER_OUT);
	}
    }
}

void		Game::_gameInteract()
{
  for (unsigned int i = 0; i < _map->getMapData().size(); i++)
    {             
      if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(),
		      IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX),
		      IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY)))
	{
	  _referee->validatePlayerAction(_gui->getMouseX(), _gui->getMouseY());
	  if (_map->getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	      == Map::CaseState::EMPTY)
	    {
	      if (_turn == Game::PLAYER1)
		_map->setCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize),
				Map::CaseState::WHITE);
	      else if (_turn == Game::PLAYER2)
		_map->setCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize),
				Map::CaseState::BLACK);
	      _turn = _turn == Game::Turn::PLAYER1 ? Game::Turn::PLAYER2 : Game::Turn::PLAYER1;
	    }
	}
    }
}

void		Game::_handleGame()
{
  if (_menuTimerContext.getState() == TimerContext::State::NONE
      && _gui->getKey() == IGui::SPACE)
    {
      _context = Context::MENU;
      _menuTimerContext.setState(TimerContext::State::PUSHED);
    }
  _displayInGameBackground();
  _displayGameBoard();
  _updateMap();
  _displayPlayerInfo();

  if (_gui->buttonLeftIsClicked())
    {
      if (_clickTimerContext.getState() == TimerContext::State::NONE ||
	  _clickTimerContext.getState() == TimerContext::State::TIMER_OUT)
	{
	  _lastClick = std::chrono::system_clock::now();
	  _clickTimerContext.setState(TimerContext::State::TIMER_IN);
	  _gameInteract();
	}
      if (_clickTimerContext.getState() == TimerContext::State::TIMER_IN)
	{
	  if (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastClick).count()
	      > timerClick)
	    {
	      _lastClick = _now;
	      _clickTimerContext.setState(TimerContext::State::TIMER_OUT);
	    }
	}
    }
  _now = std::chrono::system_clock::now();
  if (_menuTimerContext.getState() == TimerContext::State::PUSHED)
    {
      _lastTick = std::chrono::system_clock::now();
      _menuTimerContext.setState(TimerContext::State::TIMER_IN);
    }
  if (_menuTimerContext.getState() == TimerContext::State::TIMER_IN)
    {
      if (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastTick).count()
	  > timerMenu)
	{
	  _lastTick = _now;
	  _menuTimerContext.setState(TimerContext::State::NONE);
	}
    }
}

void		Game::_handleWaiting()
{
  if (_waitingTimerContext.getState() == TimerContext::State::NONE)
    {
      _lastTick = std::chrono::system_clock::now();
      _waitingTimerContext.setState(TimerContext::State::PUSHED);
    }
  _now = std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastTick).count()
      > timerWaiting)
    {
      std::cout << "[TIMER::WAITING] is finished" << std::endl;
      _lastTick = _now;
      if (_gui->buttonLeftIsClicked())
	{
	  _gameInteract();
	}
      _context = Context::GAME;
      _waitingTimerContext.setState(TimerContext::State::TIMER_OUT);
    }
  else
    {
      _gui->fillRec(0, 0, 800, 600, 0x000000);
      std::string	dot;
      for (unsigned int i = 0; i <
	     std::chrono::duration_cast<std::chrono::
	     milliseconds>(_now - _lastTick).count() / 100; i++)
	if (i < 3)
	  dot += ".";
      _gui->writeAt("waiting" + dot, (800/2) - 50, (600/2) - 50, 0x00ff00, 1.2);
      _waitingTimerContext.setState(TimerContext::State::TIMER_IN);
    }
}
