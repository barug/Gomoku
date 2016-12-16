//
// GomokuUI.cpp for Gomoku
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Tue Dec  6 02:06:49 2016 bogard_t
// Last update Sat Dec 10 19:38:21 2016 bogard_t
//

# include	<iostream>
# include	"GomokuUI.hpp"

GomokuUI::GomokuUI(IGui &gui, Map &map) : _gui(gui),
					  _map(map),
					  _timer(new Timer),
					  _context(Context::START_SCREEN),
					  _restart(false)
{
  _map.resetAllCases();
}

GomokuUI::~GomokuUI()
{
}

void			GomokuUI::setContext(const GomokuUI::Context context)
{
  _context = context;
}

GomokuUI::Context	GomokuUI::getContext(void) const
{
  return _context;
}

Map::Coordinates	*GomokuUI::getClickedTile(void)
{
  if (_gui.buttonLeftIsClicked())
    for (unsigned int i = 0; i < Map::boardSize; i++)
      if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(),
			  IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX),
			  IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY)))
	if (_map.getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	    == Map::CaseState::EMPTY)
	  return new Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize);
  return NULL;
}

bool			GomokuUI::getClicked(void) const
{
  return _gui.buttonLeftIsClicked();
}

void		        GomokuUI::displayMenu(void)
{
  if (!_timer->currentTimer(300) && _gui.getKey() == IGui::SPACE)
    {
      _context = GomokuUI::Context::GAME;
      _timer->setState(Timer::State::NONE);
    }

  _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
  _gui.writeAt("MENU", 400, 70, 0x00ff00, 1.2);
  _gui.fillRec(390, 115, 100, 2, 0x00ff00);

  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 410, 170, 40, 40))
    {
      if (_gui.buttonLeftIsClicked())
	{
	  _context = Context::WAITING;
	  _timer->setState(Timer::State::NONE);
	  _restart = true;
	  _map.resetAllCases();
	}
      else
	_gui.writeAt("> HOME", 380, 170, 0x00ff00, 1.2);
    }
  else
    _gui.writeAt("HOME", 390, 170, 0xc60000, 1.2);
  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 410, 270, 40, 40))
    {
      if (_gui.buttonLeftIsClicked())
	{
	  _context = Context::WAITING;
	  _timer->setState(Timer::State::NONE);
	}
      else
	_gui.writeAt("> BACK TO GAME", 320, 270, 0x00ff00, 1.2);
    }
  else
    _gui.writeAt("BACK TO GAME", 330, 270, 0xc60000, 1.2);

}

IPlayer::Type		GomokuUI::displayStartScreen(void)
{
  if (_restart)
    _restart = !_restart;
  _gui.setTextureAt("./sprites/background.jpg", 0, 0, 1.);
  _gui.setTextureAt("./sprites/gomoku.png", 130, 100, 0.4);
  _gui.writeAt("project for tek3 by : barthe_g, billot_t, bloy_j, bogard_t", 230, 560, 0xffffff, 0.5);
  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 400, 340, 40, 40))
    {
      if (_gui.buttonLeftIsClicked())
	return IPlayer::Type::HUMAN;
      _gui.fillRec(300, 300, 200, 80, 0x000000, 150);
      _gui.writeAt("Player vs Player", 315, 325, 0x00ff00, 0.8);
    }
  else
    {
      _gui.fillRec(300, 300, 200, 80, 0xffffff, 180);
      _gui.writeAt("Player vs Player", 315, 325, 0x000000, 0.8);
    }
  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 400, 440, 40, 40))
    {
      if (_gui.buttonLeftIsClicked())
	return IPlayer::Type::AI;
      _gui.fillRec(300, 400, 200, 80, 0x000000, 150);
      _gui.writeAt("Player vs AI", 340, 425, 0x00ff00, 0.8);
    }
  else
    {
      _gui.fillRec(300, 400, 200, 80, 0xffffff, 180);
      _gui.writeAt("Player vs AI", 340, 425, 0x000000, 0.8);
    }
  return IPlayer::Type::NONE;
}

void			GomokuUI::displayWaiting(void)
{
  std::string           displayDot;

  if (_timer->currentTimer(500))
    {
      for (unsigned int i = 0; i < _timer->timeLeft() / 100 && i < 3; i++)
	displayDot += ".";
      _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
      _gui.writeAt("waiting" + displayDot, (800/2) - 50, (600/2) - 50, 0x00ff00, 1.2);
    }
  else
    {
      _context = _restart ? Context::START_SCREEN : Context::GAME;
      _timer->setState(Timer::State::NONE);
    }
}

void			GomokuUI::displayGame(void)
{
  if (!_timer->currentTimer(300) && _gui.getKey() == IGui::SPACE)
    {
      _context = GomokuUI::Context::MENU;
      _timer->setState(Timer::State::NONE);
    }
}

void			GomokuUI::displayUI(const unsigned int scoreJ1,
					    const unsigned int scoreJ2,
					    const unsigned int captureJ1,
					    const unsigned int captureJ2)
{
  _gui.setTextureAt("./sprites/background.jpg", 0, 0);
  _gui.fillRec(10, 10, 180, 290, 0x000000, 100);
  _gui.fillRec(10, 310, 180, 280, 0x000000, 100);
  _gui.setTextureAt("./sprites/wood.jpg", 205, 9, 0.975);

  _gui.writeAt("SCORE J1 : " + std::to_string(scoreJ1), 30, 50, 0xffffff, 0.7);
  _gui.fillRec(30, 75, 88, 1, 0xffffff);
  _gui.writeAt("CAPTURE : " + std::to_string(captureJ1), 30, 150, 0xffffff, 0.7);
  _gui.fillRec(30, 175, 80, 1, 0xffffff);

  _gui.writeAt("SCORE J2 : " + std::to_string(scoreJ2), 30, 350, 0xffffff, 0.7);
  _gui.fillRec(30, 375, 88, 1, 0xffffff);
  _gui.writeAt("CAPTURE : " + std::to_string(captureJ2), 30, 450, 0xffffff, 0.7);
  _gui.fillRec(30, 475, 80, 1, 0xffffff);
}

void			GomokuUI::displayWinScreen(const std::string &msg)
{
  _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
  _gui.writeAt(msg, 300-(msg.size()*2) + 50, 120, 0xffffff, 1.);
  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 410, 270, 40, 40))
    {
      if (_gui.buttonLeftIsClicked())
	{
	  _context = Context::START_SCREEN;
	  _restart = true;
	  _timer->setState(Timer::State::NONE);
	  _map.resetAllCases();
	}
      else
	_gui.writeAt("> BACK TO HOME", 320, 270, 0x00ff00, 1.2);
    }
  else
    _gui.writeAt("BACK TO HOME", 330, 270, 0xc60000, 1.2);
}

void		        GomokuUI::updateMap(void)
{
  for (unsigned int x = 0; x < IGui::mapSize - 1; x++)
    {
      for (unsigned int y = 0; y < IGui::mapSize - 1; y++)
	{
	  _gui.fillRec(IGui::offsetMapX + (x * IGui::offsetX),
		       IGui::offsetMapY + (y * IGui::offsetY), 30, 2, 0x000000);
	  _gui.fillRec(IGui::offsetMapX + (x * IGui::offsetX),
		       IGui::offsetMapY + (y * IGui::offsetY), 2, 30, 0x000000);
	}
    }
  _gui.fillRec(IGui::offsetMapX + ((IGui::mapSize - 1) * IGui::offsetX),
	       IGui::offsetMapY + (0 * IGui::offsetY),
	       2, (IGui::offsetY * (IGui::mapSize - 1)) + 2, 0x000000);
  _gui.fillRec(IGui::offsetMapX + (0 * IGui::offsetX),
	       IGui::offsetMapY + ((IGui::mapSize - 1) * IGui::offsetY),
	       (IGui::offsetX * (IGui::mapSize - 1)) + 1, 2, 0x000000);

  for (unsigned int i = 0; i < Map::boardSize; i++)
    {
      if (_map.getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	  == Map::CaseState::WHITE)
	_gui.setTextureAt("./sprites/white.png",
			  IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
			  IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1);
      else if (_map.getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	       == Map::CaseState::BLACK)
	_gui.setTextureAt("./sprites/black.png",
			  IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
			  IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1);
      if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(),
			  IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetY),
			  IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetX))
	  && _context == Context::GAME)
	(_map.getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	 == Map::CaseState::EMPTY) ?
	  _gui.setTextureAt("./sprites/cercle_vert.png",
			    IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
			    IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1) :
	  _gui.setTextureAt("./sprites/cercle_rouge.png",
			    IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX) - 9,
			    IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY) - 9, 0.1);
    }
}

void                    GomokuUI::unvalidStep(const unsigned int x,
                                              const unsigned int y)
{
  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(),
                      IGui::offsetMapX + ((x) * IGui::offsetY),
                      IGui::offsetMapY + ((y) * IGui::offsetX))
      && _map.getCaseAt(Map::Coordinates(x, y)) == Map::CaseState::EMPTY
      && _context == Context::GAME)
    {
      _gui.setTextureAt("./sprites/cercle_rouge.png",
                        IGui::offsetMapX + ((x) * IGui::offsetX) - 9,
                        IGui::offsetMapY + ((y) * IGui::offsetY) - 9, 0.1);
      _gui.writeAt("UNVALID", 430, 115, 0xc60000, 1.3);
    }
}
