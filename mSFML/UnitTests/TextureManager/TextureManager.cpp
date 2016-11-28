//
// TextureManager.cpp for RType in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML/includes
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Sat Nov 19 11:34:37 2016 Thomas Billot
// Last update Sat Nov 19 15:58:05 2016 Thomas Billot
//

#include <cstdio>
#include <iostream>
#include "TextureManager.hpp"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

const mSFML_Textures			*TextureManager::load(const std::string &path)
{
  if (_textures[path].get() != NULL)
    return (_textures[path].get());
  mSFML_Textures			*tmp = new mSFML_Textures;
  
  if (!tmp->loadFromFile(path))
    return (NULL);
  tmp->setPath(path);
  _textures[path] = std::move(std::unique_ptr<mSFML_Textures>(tmp));
  return (_textures[path].get());
}
