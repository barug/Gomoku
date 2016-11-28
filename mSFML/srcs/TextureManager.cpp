//
// TextureManager.cpp for RType in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Sat Nov 19 11:34:37 2016 Thomas Billot
// Last update Mon Nov 28 16:57:51 2016 bogard_t
//

#include <cstdio>
#include <iostream>
#include "TextureManager.hpp"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

const sf::Texture			*TextureManager::load(const std::string &path)
{
  if (_textures[path].get() != NULL)
    return (_textures[path].get());
  sf::Texture			*tmp = new sf::Texture;

  if (!tmp->loadFromFile(path))
    return (NULL);
  _textures[path] = std::move(std::unique_ptr<sf::Texture>(tmp));
  return (_textures[path].get());
}
