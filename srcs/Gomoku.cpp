//
// Gomoku.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Thu Dec  1 13:27:10 2016 bogard_t
//

# include	<cstdio>
# include	<iostream>
# include	"Gomoku.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

Gomoku::Gomoku() : _gui(new mSFML_Window(std::string("Gomoku"), 800, 600)),
		   _map(new Map)
{
  _gui->loadFont("./font/digital.otf");
  for (unsigned int x = 0; x < 19; x++)
    for (unsigned int y = 0; y < 19; y++)
      _map->setCaseAt(Map::Coordinates(x, y), Map::CaseState::EMPTY);
}

Gomoku::~Gomoku()
{
  delete _gui;
  delete _map;
}

bool		Gomoku::_magnetTile(const unsigned int mouseX,
				    const unsigned int mouseY,
				    const unsigned int x,
				    const unsigned int y,
				    const unsigned int intensity) const
{
  for (unsigned int i = 0; i < intensity; i++)
    {
      for (unsigned int j = 0; j < intensity; j++)
	{
	  // menger square
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

void		Gomoku::_displayPlayerInfo() const
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

void		Gomoku::_displayBackground() const
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

void		Gomoku::_displayGameBoard() const
{
  for (unsigned int x = 0; x < 18; x++)
    {
      for (unsigned int y = 0; y < 18; y++)
	{
	  _gui->fillRec(Map::offsetMapX + (x * Map::offsetX),
			Map::offsetMapY + (y * Map::offsetY), 30, 2, 0x000000);
	  _gui->fillRec(Map::offsetMapX + (x * Map::offsetX),
			Map::offsetMapY + (y * Map::offsetY), 2, 30, 0x000000);
	}
    }

  _gui->fillRec(Map::offsetMapX + (18 * Map::offsetX),
		Map::offsetMapY + (0 * Map::offsetY),
		2, (Map::offsetY * 18) + 2, 0x000000);

  _gui->fillRec(Map::offsetMapX + (0 * Map::offsetX),
		Map::offsetMapY + (18 * Map::offsetY),
		(Map::offsetX * 18) + 1, 2, 0x000000);
}

void		Gomoku::_updateMap()
{
  for (unsigned int i = 0; i < _map->getMapData().size(); i++)
    {
      if (_map->getCaseAt(Map::Coordinates(i % Map::mapSize, i / Map::mapSize))
	  == Map::CaseState::WHITE)
	{
  	  _gui->setTextureAt("./sprites/white.png",
  			     Map::offsetMapX + ((i % Map::mapSize) * Map::offsetX) - 9,
  			     Map::offsetMapY + ((i / Map::mapSize) * Map::offsetY) - 9, 0.1);
  	}
      else if (_map->getCaseAt(Map::Coordinates(i % Map::mapSize, i / Map::mapSize))
	       == Map::CaseState::BLACK)
	{
	  _gui->setTextureAt("./sprites/black.png",
  			     Map::offsetMapX + ((i % Map::mapSize) * Map::offsetX) - 9,
  			     Map::offsetMapY + ((i / Map::mapSize) * Map::offsetY) - 9, 0.1);
  	}
      if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(),
      		      Map::offsetMapX + ((i % Map::mapSize) * Map::offsetY),
      		      Map::offsetMapY + ((i / Map::mapSize) * Map::offsetX)))
  	{
	  (_map->getCaseAt(Map::Coordinates(i % Map::mapSize, i / Map::mapSize))
			   == Map::CaseState::EMPTY) ?
	   _gui->setTextureAt("./sprites/cercle_vert.png",
			      Map::offsetMapX + ((i % Map::mapSize) * Map::offsetX) - 9,
			      Map::offsetMapY + ((i / Map::mapSize) * Map::offsetY) - 9, 0.1) :
	   _gui->setTextureAt("./sprites/cercle_rouge.png",
			      Map::offsetMapX + ((i % Map::mapSize) * Map::offsetX) - 9,
			      Map::offsetMapY + ((i / Map::mapSize) * Map::offsetY) - 9, 0.1);
  	}
    }
}

void		Gomoku::_checkIfClicked()
{
  if (_gui->buttonLeftIsClicked())
    {
      for (unsigned int i = 0; i < _map->getMapData().size(); i++)
	{
      	  if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(),
	  		  Map::offsetMapX + ((i % Map::mapSize) * Map::offsetX),
	  		  Map::offsetMapY + ((i / Map::mapSize) * Map::offsetY)))
	    {
	      if (_map->getCaseAt(Map::Coordinates(i % Map::mapSize, i / Map::mapSize))
				  == Map::CaseState::EMPTY)
		{
		  // check if its possible by the referee
		  _map->setCaseAt(Map::Coordinates(i % Map::mapSize, i / Map::mapSize),
				  Map::CaseState::WHITE);
		  std::cout << "[DEBUG] => [PIXEL] >> x [" << _gui->getMouseX()
			    << "] and y [" << _gui->getMouseY()
			    << "] [REAL--->] x [" << i % Map::mapSize
			    << "] -> y [" << i / Map::mapSize << "]" << std::endl;
		}
	    }
	}
    }
}

int		Gomoku::start()
{
  while (_gui->isAlive())
    {
      _gui->clear();
      _gui->handleEvents();

      _displayBackground();
      _displayGameBoard();

      _updateMap();

      _checkIfClicked();

      _displayPlayerInfo();
      _gui->display();
    }
  return 0;
}
