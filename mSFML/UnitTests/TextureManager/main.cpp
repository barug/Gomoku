//
// main.cpp for UnitTes in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML/UnitTests/TextureManager
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Sat Nov 19 15:31:00 2016 Thomas Billot
// Last update Sat Nov 19 15:59:03 2016 Thomas Billot
//

#include <iostream>
#include <cassert>
#include <cstring>
#include "TextureManager.hpp"

#define PATH	"../../sprites/"

int		main()
{
  TextureManager	_manager;

  assert(_manager.load("../../../sprites/r-typesheet1.gif") != NULL);
  assert(_manager.load("../../../sprites/r-typesheet2.gif") != NULL);
  assert(_manager.load("../../../sprites/r-typesheet3.gif") != NULL);
  assert(_manager.load("../../../sprites/r-typesheet40.gif") != NULL);
  assert(_manager.load("../../../sprites/r-typesheet1.gif") != NULL);
  assert(_manager.load("../../../sprites/r-typesheet2.gif") != NULL);
  assert(_manager.load("../../../sprites/r-typesheet3.gif") != NULL);
  assert(_manager.load("../../../sprites/r-typesheet40.gif") != NULL);
  assert(_manager.load("TESTQUIFAIL") == NULL);

  std::cout << "Everything did go as planned" << std::endl;
  return (0);
}
