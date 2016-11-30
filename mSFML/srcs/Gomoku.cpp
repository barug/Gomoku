//
// Gomoku.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 13:20:55 2016 bogard_t
// Last update Wed Nov 30 15:00:30 2016 bogard_t
//

# include	<cstdio>
# include	<iostream>
# include	"Gomoku.hpp"
# include	"mSFML_Window.hpp"
# include	"mSFML_Audio.hpp"

Gomoku::Gomoku() : _gui(new mSFML_Window(std::string("Gomoku"), 800, 600))
{
  _gui->loadFont("./font/digital.otf");
  for (unsigned int x = 0; x < 19; x++)
    for (unsigned int y = 0; y < 19; y++)
      _vecCase.push_back(new Case(x, y, 230 + (x * 30), 20 + (y * 30)));
}

Gomoku::~Gomoku()
{
  delete _gui;
}

bool		Gomoku::_magnetTile(const unsigned int mouseX,
				    const unsigned int mouseY,
				    const unsigned int x,
				    const unsigned int y,
				    const unsigned int intensity)
{
  for (unsigned int i = 0; i < intensity; i++)
    {
      for (unsigned int j = 0; j < intensity; j++)
	{
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

void		Gomoku::_displayPlayerInfo()
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

void		Gomoku::_displayBackground()
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

void		Gomoku::_displayGameBoard()
{

  for (unsigned int x = 0; x < 18; x++)
    {
      for (unsigned int y = 0; y < 18; y++)
	{
	  if (x != 18 && y != 18)
	    {
	      _gui->fillRec(230 + (x * 30), 20 + (y * 30), 30, 2, 0x000000);
	      _gui->fillRec(230 + (x * 30), 20 + (y * 30), 2, 30, 0x000000);
	    }
	}
    }
  _gui->fillRec(230 + (18 * 30), 20 + (0 * 30), 2, (30 * 18) + 2, 0x000000);
  _gui->fillRec(230 + (0 * 30), 20 + (18 * 30), (30 * 18) + 1, 2, 0x000000);

}

void		Gomoku::_updateMap()
{
  for (auto it : _vecCase)
    {
      if (it->getColorSlot() != Case::ColorSlot::NONE)
	{
	  std::cout << "case x : " << it->getX() << "\ty : " << it->getY()<< std::endl;
	}
      if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(), it->getXPixel(), it->getYPixel()))
	{
	  _gui->setTextureAt("./sprites/cercle_vert.png",
			     it->getXPixel()-9,
			     it->getYPixel()-9,
			     0.1);
	}
      if (it->getColorSlot() == Case::ColorSlot::WHITE)
	{
	  _gui->setTextureAt("./sprites/white.png",
			     it->getXPixel()-9,
			     it->getYPixel()-9,
			     0.1);
	}
      else if (it->getColorSlot() == Case::ColorSlot::BLACK)
	{
	  _gui->setTextureAt("./sprites/black.png",
			     it->getXPixel()-9,
			     it->getYPixel()-9,
			     0.1);
	}
    }
}

void		Gomoku::_checkIfClicked()
{
  if (_gui->buttonLeftIsClicked())
    {
      for (auto it : _vecCase)
	{
	  if (_magnetTile(_gui->getMouseX(), _gui->getMouseY(), it->getXPixel(), it->getYPixel()))
	    {
	      it->setColorSlot(Case::ColorSlot::WHITE);
	      std::cout << "[clicked on] x : " << _gui->getMouseX()
			<< " and y : " << _gui->getMouseY() << std::endl;

	    }
	}
    }

}

void		Gomoku::start()
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
}
