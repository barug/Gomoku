//
// BoardGame.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Thu Dec  1 17:43:13 2016 bogard_t
//

# include	<cstdio>
# include	<iostream>
# include	"BoardGame.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

BoardGame::BoardGame() : _gui(new mSFML_Window(std::string("Gomoku - 2016"), 800, 600)),
			 _map(new Map),
			 _context(STARTSCREEN)
{
  _gui->loadFont("./font/digital.otf");
  for (unsigned int x = 0; x < IGui::mapSize; x++)
    for (unsigned int y = 0; y < IGui::mapSize; y++)
      _map->setCaseAt(Map::Coordinates(x, y), Map::CaseState::EMPTY);
}

BoardGame::~BoardGame()
{
  delete _gui;
  delete _map;
}

bool		BoardGame::_magnetTileCircle(const unsigned int mouseX,
					     const unsigned int mouseY,
					     const unsigned int x,
					     const unsigned int y,
					     const unsigned int intensityX,
					     const unsigned int intensityY) const
{
  for (unsigned int i = 0; i < intensityX; i++)
    {
      for (unsigned int j = 0; j < intensityY; j++)
	{
	  // menger sponge (joke)
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
	}
    }
  return (false);
}

void		BoardGame::_displayPlayerInfo() const
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

void		BoardGame::_displayInGameBackground() const
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

void		BoardGame::_displayStartScreen()
{
  _gui->setTextureAt("./sprites/background.jpg", 0, 0, 0.5);
  _gui->setTextureAt("./sprites/gomoku.png", 130, 100, 0.4);

  if (_magnetTileCircle(_gui->getMouseX(), _gui->getMouseY(),
  			400, 340, 100, 40))
    {
      if (_gui->buttonLeftIsClicked())
	_context = Context::GAME;
      _gui->fillRec(300, 300, 200, 80, 0xff0000, 180);
      _gui->writeAt("Player vs Player", 315, 325, 0xffffff, 0.8);
    }
  else
    {
      _gui->fillRec(300, 300, 200, 80, 0xffffff, 180);
      _gui->writeAt("Player vs Player", 315, 325, 0x000000, 0.8);
    }

  if (_magnetTileCircle(_gui->getMouseX(), _gui->getMouseY(),
  			400, 440, 100, 40))
    {
      if (_gui->buttonLeftIsClicked())
	_context = Context::GAME;
      _gui->fillRec(300, 400, 200, 80, 0xff0000, 180);
      _gui->writeAt("Player vs AI", 340, 425, 0xffffff, 0.8);
    }
  else
    {
      _gui->fillRec(300, 400, 200, 80, 0xffffff, 180);
      _gui->writeAt("Player vs AI", 340, 425, 0x000000, 0.8);
    }

}

void		BoardGame::_displayGameBoard() const
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

void		BoardGame::_updateMap()
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
      if (_magnetTileCircle(_gui->getMouseX(), _gui->getMouseY(),
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

void		BoardGame::_gameInteract()
{
  for (unsigned int i = 0; i < _map->getMapData().size(); i++)
    {
      if (_magnetTileCircle(_gui->getMouseX(), _gui->getMouseY(),
			    IGui::offsetMapX + ((i % IGui::mapSize) * IGui::offsetX),
			    IGui::offsetMapY + ((i / IGui::mapSize) * IGui::offsetY)))
	{
	  if (_map->getCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize))
	      == Map::CaseState::EMPTY)
	    {
	      // check if its possible by the referee
	      _map->setCaseAt(Map::Coordinates(i % IGui::mapSize, i / IGui::mapSize),
			      Map::CaseState::WHITE);
	      std::cout << "[DEBUG] => [PIXEL] >> x [" << _gui->getMouseX()
			<< "] and y [" << _gui->getMouseY()
			<< "] [REAL--->] x [" << i % IGui::mapSize
			<< "] -> y [" << i / IGui::mapSize << "]" << std::endl;
	    }
	}
    }
}

int		BoardGame::start()
{
  while (_gui->isAlive())
    {
      _gui->clear();
      _gui->handleEvents();

      if (_context == Context::STARTSCREEN)
	_displayStartScreen();

      if (_context == Context::GAME || _context == Context::MENU)
	{
	  _displayInGameBackground();
	  _displayGameBoard();
	  _updateMap();
	  if (_gui->buttonLeftIsClicked())
	    _gameInteract();
	  _displayPlayerInfo();
	}

      _gui->display();
    }
  return 0;
}
