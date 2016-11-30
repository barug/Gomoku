//
// test.cpp for Gomuko in /home/mikaz3/Tek3/B5/AI
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Oct 12 11:52:44 2016 Thomas Billot
// Last update Wed Nov 30 13:00:08 2016 bogard_t
//

#include	<cstdio>
#include	<iostream>
#include	"mSFML_Window.hpp"
#include	"mSFML_Audio.hpp"
#include	"Case.hpp"

static bool		magnetTile(const unsigned int mouseX,
				   const unsigned int mouseY,
				   const unsigned int x,
				   const unsigned int y,
				   const unsigned int intensity = 8)
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

int			main(int , char **)
{
  IGui			*win = new mSFML_Window(std::string("Gomoku"), 800, 600);
  bool			initVec = false;
  std::vector<Case*>	vec_case;

  win->loadFont("./font/digital.otf");
  while (win->isAlive())
    {
      win->clear();
      win->handleEvents();

      // background
      win->fillRec(0, 0, 800, 600, 0xffffff);
      win->fillRec(0, 0, 190, 600, 0x000000);
      win->fillRec(0, 300, 200, 10, 0xffffff);
      win->setTextureAt("./sprites/wood.jpg", 200, 0, 1.);

      // up
      win->fillRec(0, 0, 800, 10, 0xffffff);
      // down
      win->fillRec(0, 590, 800, 10, 0xffffff);
      // right
      win->fillRec(790, 0, 10, 800, 0xffffff);
      // left
      win->fillRec(0, 0, 10, 600, 0xffffff);

      // map updating
      for (unsigned int x = 0; x < 19; x++)
	{
	  for (unsigned int y = 0; y < 19; y++)
	    {
	      if (!initVec)
		vec_case.push_back(new Case(x, y, 230 + (x * 30), 20 + (y * 30)));
	      if (x != 18 && y != 18)
		{
		  win->fillRec(230 + (x * 30), 20 + (y * 30), 30, 2, 0x000000);
		  win->fillRec(230 + (x * 30), 20 + (y * 30), 2, 30, 0x000000);
		}
	    }
	}
      initVec = true;
      win->fillRec(230 + (18 * 30), 20 + (0 * 30), 2, (30 * 18), 0x000000);
      win->fillRec(230 + (0 * 30), 20 + (18 * 30), (30 * 18), 2, 0x000000);

      for (auto it : vec_case)
	{
	  if (it->getColorSlot() != Case::ColorSlot::NONE)
	    {
	      std::cout << "case x : " << it->getX() << "\ty : " << it->getY()<< std::endl;
	    }
	  if (magnetTile(win->getMouseX(), win->getMouseY(), it->getXPixel(), it->getYPixel()))
	    {
	      win->setTextureAt("./sprites/cercle_vert.png",
				it->getXPixel()-9,
				it->getYPixel()-9,
				0.1);
	    }
	  if (it->getColorSlot() == Case::ColorSlot::WHITE)
	    {
	      win->setTextureAt("./sprites/white.png",
				it->getXPixel()-9,
				it->getYPixel()-9,
				0.1);
	    }
	  else if (it->getColorSlot() == Case::ColorSlot::BLACK)
	    {
	      win->setTextureAt("./sprites/black.png",
				it->getXPixel()-9,
				it->getYPixel()-9,
				0.1);
	    }
	}


      if (win->buttonLeftIsClicked())
	{
	  for (auto it : vec_case)
	    {
	      if (magnetTile(win->getMouseX(), win->getMouseY(), it->getXPixel(), it->getYPixel()))
		{
		  it->setColorSlot(Case::ColorSlot::WHITE);
		  std::cout << "[clicked on] x : " << win->getMouseX()
			    << " and y : " << win->getMouseY() << std::endl;

		}
	    }
	}

      // score
      win->writeAt("SCORE J1 :", 40, 50, 0xffffff, 0.5);
      win->fillRec(40, 70, 60, 1, 0xffffff);
      win->writeAt("PIONS RESTANTS :", 40, 100, 0xffffff, 0.5);
      win->fillRec(40, 120, 100, 1, 0xffffff);
      win->writeAt("ALIGNEMENT :", 40, 150, 0xffffff, 0.5);
      win->fillRec(40, 170, 75, 1, 0xffffff);

      win->writeAt("SCORE J2 :", 40, 350, 0xffffff, 0.5);
      win->fillRec(40, 370, 60, 1, 0xffffff);
      win->writeAt("PIONS RESTANTS :", 40, 400, 0xffffff, 0.5);
      win->fillRec(40, 420, 100, 1, 0xffffff);
      win->writeAt("ALIGNEMENT :", 40, 450, 0xffffff, 0.5);
      win->fillRec(40, 470, 75, 1, 0xffffff);

      // display new elements on screen
      win->display();
    }
  return (0);
}
