//
// GomokuUI.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Tue Dec  6 02:06:49 2016 bogard_t
// Last update Tue Dec  6 02:53:53 2016 bogard_t
//

# include	<iostream>
# include	"GomokuUI.hpp"

GomokuUI::GomokuUI(IGui &gui, Map &map) : _gui(gui),
					  _map(map),
					  _timer(new Timer),
					  _context(Context::STARTSCREEN),
					  _restart(false)
{
  _map.resetAllCases(IGui::mapSize);
}

GomokuUI::~GomokuUI()
{
  delete _timer;
}

void			GomokuUI::setContext(GomokuUI::Context context)
{
  _context = context;
}

GomokuUI::Context	GomokuUI::getContext() const
{
  return _context;
}

Map::Coordinates	*GomokuUI::getClickedTile()
{
  if (_gui.buttonLeftIsClicked())
    for (unsigned int i = 0; i < _map.getMapData().size(); i++)
      if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(),
		     IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX),
		     IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY)))
	if (_map.getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	    == Map::CaseState::EMPTY)
	  return (new Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize));
  return (NULL);
}

bool			GomokuUI::getClicked() const
{
  return (_gui.buttonLeftIsClicked());
}

void		        GomokuUI::displayMenu()
{
  if (!_timer->currentTimer(300) and _gui.getKey() == IGui::SPACE)
    {
      _context = GomokuUI::Context::GAME;
      _timer->setState(Timer::State::NONE);
    }
  _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
  _gui.writeAt("MENU", 400, 70, 0x00ff00, 1.2);
  _gui.fillRec(390, 115, 100, 2, 0x00ff00);
  _gui.writeAt("BACK TO GAME", 330, 270, 0x00ff00, 1.2);
  _gui.writeAt("BACK TO HOME", 330, 370, 0x00ff00, 1.2);
  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 410, 370, 60, 30) and
      _gui.buttonLeftIsClicked())
    {
      _context = Context::WAITING;
      _timer->setState(Timer::State::NONE);
      _restart = true;
      _map.resetAllCases(IGui::mapSize);
    }
  else if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 410, 270, 60, 30) and
	   _gui.buttonLeftIsClicked())
    {
      _context = Context::WAITING;
      _timer->setState(Timer::State::NONE);
    }
}

void			GomokuUI::displayStartScreen(Player *player2)
{
  if (_restart)
    _restart = !_restart;

  _gui.setTextureAt("./sprites/background.jpg", 0, 0, 0.5);
  _gui.setTextureAt("./sprites/gomoku.png", 130, 100, 0.4);
  _gui.writeAt("project for tek3 by : barthe_g, billot_t, bloy_j, bogard_t", 230, 560, 0xffffff, 0.5);
  if (_gui.magnetTile(_gui.getMouseX(), _gui.getMouseY(), 400, 340, 40, 40))
    {
      if (_gui.buttonLeftIsClicked())
	_context = Context::WAITING;
      _gui.fillRec(300, 300, 200, 80, 0x000000, 180);
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
	{
	  _context = Context::WAITING;
	  player2->setType(Player::Type::AI);
	}
      _gui.fillRec(300, 400, 200, 80, 0x000000, 180);
      _gui.writeAt("Player vs AI", 340, 425, 0x00ff00, 0.8);
    }
  else
    {
      _gui.fillRec(300, 400, 200, 80, 0xffffff, 180);
      _gui.writeAt("Player vs AI", 340, 425, 0x000000, 0.8);
    }
}

void			GomokuUI::displayWaiting()
{
  if (_timer->currentTimer(500))
    {
      std::string	displayDot;

      for (unsigned int i = 0; i < _timer->timeLeft() / 100 && i < 3; i++)
	displayDot += ".";
      _gui.fillRec(0, 0, 800, 600, 0x000000);
      _gui.writeAt("waiting" + displayDot, (800/2) - 50, (600/2) - 50, 0x00ff00, 1.2);
    }
  else
    {
      _context = _restart ? Context::STARTSCREEN : Context::GAME;
      _timer->setState(Timer::State::NONE);
    }
}

void			GomokuUI::displayGame()
{
  if (!_timer->currentTimer(300) and _gui.getKey() == IGui::SPACE)
    {
      _context = GomokuUI::Context::MENU;
      _timer->setState(Timer::State::NONE);
    }
}

// update map
void		        GomokuUI::updateMap()
{
  // display background
  _gui.setTextureAt("./sprites/horrible.jpg", 0, 0);
  _gui.fillRec(10, 10, 180, 290, 0x000000);
  _gui.fillRec(10, 310, 180, 280, 0x000000);
  _gui.setTextureAt("./sprites/wood.jpg", 205, 9, 0.975);

  // display players infos
  _gui.writeAt("SCORE J1 :", 40, 50, 0xffffff, 0.5);
  _gui.fillRec(40, 70, 60, 1, 0xffffff);
  _gui.writeAt("PIONS RESTANTS :", 40, 100, 0xffffff, 0.5);
  _gui.fillRec(40, 120, 100, 1, 0xffffff);
  _gui.writeAt("ALIGNEMENT :", 40, 150, 0xffffff, 0.5);
  _gui.fillRec(40, 170, 75, 1, 0xffffff);
  _gui.writeAt("SCORE J2 :", 40, 350, 0xffffff, 0.5);
  _gui.fillRec(40, 370, 60, 1, 0xffffff);
  _gui.writeAt("PIONS RESTANTS :", 40, 400, 0xffffff, 0.5);
  _gui.fillRec(40, 420, 100, 1, 0xffffff);
  _gui.writeAt("ALIGNEMENT :", 40, 450, 0xffffff, 0.5);
  _gui.fillRec(40, 470, 75, 1, 0xffffff);

  // display checkerboard
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

  // update map
  for (unsigned int i = 0; i < _map.getMapData().size(); i++)
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
	  and _context == Context::GAME)
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
