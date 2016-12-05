# include	<iostream>
# include	"GomokuUI.hpp"

GomokuUI::GomokuUI(IGui &gui, Map &map) : _gui(gui),
					  _map(map),
					  _context(Context::STARTSCREEN)
{
}

GomokuUI::~GomokuUI()
{
}

void			GomokuUI::setContext(GomokuUI::Context context)
{
  _context = context;
}

GomokuUI::Context	GomokuUI::getContext() const
{
  return _context;
}

bool			GomokuUI::currentTimer(const unsigned int timer)
{
  if (_currentTimer.getState() == TimerContext::State::NONE ||
      _currentTimer.getState() == TimerContext::State::TIMER_OUT)
    {
      _lastTick = std::chrono::system_clock::now();
      _currentTimer.setState(TimerContext::State::PUSHED);
    }
  _now = std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastTick).count()
      > timer)
    {
      _lastTick = _now;
      _currentTimer.setState(TimerContext::State::TIMER_OUT);
      return (false);
    }
  else
    {
      _currentTimer.setState(TimerContext::State::TIMER_IN);
      return (true);
    }
}

Map::Coordinates	*GomokuUI::getClickedOnTile()
{
  if (_gui.buttonLeftIsClicked())
    for (unsigned int i = 0; i < _map.getMapData().size(); i++)
      if (magnetTile(_gui.getMouseX(), _gui.getMouseY(),
		     IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX),
		     IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY)))
	if (_map.getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	    == Map::CaseState::EMPTY)
	  return (new Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize));
  return (NULL);
}

bool			GomokuUI::getClicked()
{
  return (_gui.buttonLeftIsClicked() ? currentTimer(100) : false);
}

void		        GomokuUI::displayMenu()
{
  _gui.fillRec(0, 0, 800, 600, 0x000000, 180);
  _gui.writeAt("MENU", 400, 70, 0x00ff00, 1.2);
  _gui.fillRec(390, 115, 100, 2, 0x00ff00);
  _gui.writeAt("BACK TO HOME", 330, 370, 0x00ff00, 1.2);
  if (magnetTile(_gui.getMouseX(), _gui.getMouseY(), 410, 370, 50, 30) && getClicked())
    {
      _context = Context::STARTSCREEN;
      for (unsigned int x = 0; x < IGui::mapSize; x++)
	for (unsigned int y = 0; y < IGui::mapSize; y++)
	  _map.setCaseAt(Map::Coordinates(x, y), Map::CaseState::EMPTY);
    }
}

void			GomokuUI::displayStartScreen()
{
  _gui.setTextureAt("./sprites/background.jpg", 0, 0, 0.5);
  _gui.setTextureAt("./sprites/gomoku.png", 130, 100, 0.4);
  _gui.writeAt("project for tek3 by : barthe_g, billot_t, bloy_j, bogard_t", 230, 560, 0xffffff, 0.5);
  if (magnetTile(_gui.getMouseX(), _gui.getMouseY(), 400, 340, 40, 40))
    {
      if (getClicked())
	_context = Context::WAITING;
      _gui.fillRec(300, 300, 200, 80, 0x000000, 180);
      _gui.writeAt("Player vs Player", 315, 325, 0x00ff00, 0.8);
    }
  else
    {
      _gui.fillRec(300, 300, 200, 80, 0xffffff, 180);
      _gui.writeAt("Player vs Player", 315, 325, 0x000000, 0.8);
    }
  if (magnetTile(_gui.getMouseX(), _gui.getMouseY(), 400, 440, 40, 40))
    {
      if (getClicked())
	_context = Context::WAITING;
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
  if (currentTimer(500))
    {
      std::string	displayDot;

      for (unsigned int i = 0; i <
	     std::chrono::duration_cast<std::chrono::
	     milliseconds>(_now - _lastTick).count() / 100 && i < 3; i++)
	displayDot += ".";
      _gui.fillRec(0, 0, 800, 600, 0x000000);
      _gui.writeAt("waiting" + displayDot, (800/2) - 50, (600/2) - 50, 0x00ff00, 1.2);
    }
  else
    _context = Context::GAME;
}

void		        GomokuUI::updateMap()
{
  // display background
  _gui.fillRec(0, 0, 800, 600, 0xffffff);
  _gui.fillRec(0, 0, 190, 600, 0x000000);
  _gui.fillRec(0, 300, 200, 10, 0xffffff);
  _gui.setTextureAt("./sprites/wood.jpg", 200, 0, 1.);

  // display players infos
  _gui.fillRec(0, 0, 800, 10, 0xffffff);
  _gui.fillRec(0, 590, 800, 10, 0xffffff);
  _gui.fillRec(790, 0, 10, 800, 0xffffff);
  _gui.fillRec(0, 0, 10, 600, 0xffffff);
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
      if (magnetTile(_gui.getMouseX(), _gui.getMouseY(),
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

bool		        GomokuUI::magnetTile(const unsigned int mouseX,
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
