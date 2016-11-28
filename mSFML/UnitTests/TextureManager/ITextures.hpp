//
// ITextures.hpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Thu Nov 17 22:05:56 2016 Thomas Billot
// Last update Sat Nov 19 11:58:29 2016 Thomas Billot
//

#ifndef		__ITEXTURES__HPP__
# define	__ITEXTURES__HPP__

class		ITextures
{

public:

  virtual ~ITextures() {}

  virtual bool		loadFromFile(const std::string &name) = 0;
  
private:
  
};

#endif		/* __ITEXTURES__HPP__ */
