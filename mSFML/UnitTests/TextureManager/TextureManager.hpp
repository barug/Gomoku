//
// TextureManager.hpp for RType in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML/includes
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Sat Nov 19 11:30:48 2016 Thomas Billot
// Last update Sat Nov 19 12:11:55 2016 Thomas Billot
//

#ifndef			__TEXTUREMANAGER_HPP__
# define		__TEXTUREMANAGER_HPP__

# include	        <unordered_map>
# include		<memory>

# include		"mSFML_Textures.hpp"

class			TextureManager
{

public:

						TextureManager();
						~TextureManager();
  const mSFML_Textures				*load(const std::string &path);
  
private:

  std::unordered_map<std::string,
		     std::unique_ptr<mSFML_Textures>>		_textures;
  
};

#endif			/* __TEXTUREMANAGER_HPP__  */
