//
// test.cpp for Gomuko in /home/mikaz3/Tek3/B5/AI
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Oct 12 11:52:44 2016 Thomas Billot
// Last update Mon Nov 28 10:54:53 2016 bogard_t
//

#include	<cstdio>
#include	<iostream>
#include	<boost/asio.hpp>
#include	"TextureManager.hpp"
#include	"mSFML_Window.hpp"
#include	"mSFML_Audio.hpp"

int		main(int , char **)
{
  IWindow	*win = new mSFML_Window(std::string("test"), 800, 600);

  win->loadFont("./font/digital.otf");
  while (win->isAlive())
    {
      win->clear();
      win->handleEvents();

      for (unsigned int i = 0; i < 10; i++)
      	{
      	  for (unsigned int j = 0; j < 10; j++)
      	    {
      	      win->setTextureAt("./sprites/wood.png", i * 80, j * 80, 0.8);
      	    }
      	}
      if (win->buttonLeftIsClicked())
	{
	  std::cout << "[clicked on] x : " << win->getMouseX() << std::endl;
	  std::cout << "[clicked on] y : " << win->getMouseY() << std::endl;
	}
      win->writeAt("SCORE J1 :", 100, 550, 1);
      win->writeAt("SCORE J2 :", 550, 550, 1);
      win->display();
    }
  return (0);
}
