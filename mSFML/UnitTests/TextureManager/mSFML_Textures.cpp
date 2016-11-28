//
// mSFML_Textures.cpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML/includes
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Sat Nov 19 11:23:12 2016 Thomas Billot
// Last update Sat Nov 19 15:26:04 2016 Thomas Billot
//

#include <iostream>
#include "Log.hpp"
#include "mSFML_Textures.hpp"

mSFML_Textures::mSFML_Textures() : _texture(),
				   _path()
{}

mSFML_Textures::~mSFML_Textures() {}

bool			mSFML_Textures::loadFromFile(const std::string &path)
{
  if (!_texture.loadFromFile(path))
    {
      // writeinlogfile("[mSFML_Textures::loadFromFile] Error loading texture: " + path);
      std::cerr << "Error loading textures" << std::endl;
      return (false);
    }
  return (true);
}

const sf::Texture	&mSFML_Textures::getTexture() const
{
  return (_texture);
}

void			mSFML_Textures::setPath(const std::string &path)
{
  _path = path;
}

const std::string	&mSFML_Textures::getPath() const
{
  return (_path);
}
