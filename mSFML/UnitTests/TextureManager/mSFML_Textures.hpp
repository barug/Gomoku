//
// mSFML_Textures.hpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Thu Nov 17 22:04:03 2016 Thomas Billot
// Last update Sat Nov 19 14:48:30 2016 Thomas Billot
//

#ifndef			__MSFML_TEXTURES__HPP__
# define		__MSFML_TEXTURES__HPP__

# include		<SFML/Graphics.hpp>
# include	        "ITextures.hpp"

class			mSFML_Textures : public ITextures
{

public:

			mSFML_Textures();
			virtual ~mSFML_Textures();
  virtual bool	        loadFromFile(const std::string &path);
  const sf::Texture	&getTexture() const;
  void			setPath(const std::string &path);
  const std::string	&getPath() const;
  void			draw(sf::RenderWindow &win);
  
private:

  sf::Texture		_texture;
  std::string		_path;
  
};

#endif			/* __MSFML_TEXTURES__HPP__ */
