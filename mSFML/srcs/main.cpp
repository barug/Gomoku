//
// test.cpp for Gomuko in /home/mikaz3/Tek3/B5/AI
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Oct 12 11:52:44 2016 Thomas Billot
// Last update Mon Nov 28 17:24:24 2016 bogard_t
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
  // TextureManager _manager;

  // printf("Pointer [%p]\n", _manager.load("../sprites/r-typesheet10.gif"));
  // printf("Pointer [%p]\n", _manager.load("../sprites/r-typesheet12.gif"));
  // printf("Pointer [%p]\n", _manager.load("../sprites/r-typesheet13.gif"));
  // printf("Pointer [%p]\n", _manager.load("../sprites/r-typesheet10.gif"));
  // printf("Pointer [%p]\n", _manager.load("../sprites/r-typesheet12.gif"));
  // printf("Pointer [%p]\n", _manager.load("../sprites/r-typesheet13.gif"));

  win->loadFont("./digital.otf");
  while (win->isAlive())
    {
      win->clear();
      win->handleEvents();
      for (unsigned int i = 0; i < 30; i++)
	{
	  for (unsigned int j = 0; j < 20; j++)
	    {
	      win->setTextureAt("./texture.gif", i * 20, j * 20);
	    }
	}

      win->writeAt("SCORE :", 300, 550, 1.);
      win->display();
    }
  return (0);
}
