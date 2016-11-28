//
// TextureManager.hpp for RType in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Sat Nov 19 11:30:48 2016 Thomas Billot
// Last update Mon Nov 28 15:10:12 2016 bogard_t
//

#ifndef			__TEXTUREMANAGER_HPP__
# define		__TEXTUREMANAGER_HPP__

# include	        <unordered_map>
# include		<memory>
# include		<SFML/Graphics.hpp>

class			TextureManager
{

public:

  TextureManager();
  ~TextureManager();
  const sf::Texture  	*load(const std::string &path);

private:

  std::unordered_map<std::string,
		     std::unique_ptr<sf::Texture>>		_textures;

};

#endif			/* __TEXTUREMANAGER_HPP__  */
