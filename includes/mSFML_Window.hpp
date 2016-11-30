//
// mSFML_Window.hpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 16 17:07:01 2016 Thomas Billot
// Last update Wed Nov 30 03:02:07 2016 bogard_t
//

#ifndef		__MSFML__WINDOW__HPP__
# define	__MSFML__WINDOW__HPP__

# include	<SFML/Window.hpp>
# include	<SFML/Graphics.hpp>
# include	<SFML/Graphics/Font.hpp>

# include	"mSFML.hpp"
# include	"IGui.hpp"
# include	"TextureManager.hpp"

class		mSFML_Window : public IGui
{

public:

  mSFML_Window(const std::string &name = DEFAULT_WINDOW_NAME,
	       const int windowX = DEFAULT_WINDOW_X,
	       const int windowY = DEFAULT_WINDOW_Y);
  virtual ~mSFML_Window();

  /*
  ** Windows methods
  */
  virtual void		update(void);
  virtual void		display(void);
  virtual void		clear(void);
  virtual bool		isAlive(void);

  /*
  ** Keyboard Events methods
  */
  virtual IGui::Key	getKey(void) const;
  virtual void		handleEvents(void);

  /*
  ** Mouse Event
  */
  virtual unsigned int	getMouseX(void) const;
  virtual unsigned int	getMouseY(void) const;
  virtual bool	        buttonLeftIsClicked(void) const;
  virtual bool	        buttonRightIsClicked(void) const;

  /*
  ** Font methods
  */
  virtual void		loadFont(const std::string &path);
  virtual void	        writeAt(const std::string  &msg,
				const float x, const float y,
				const unsigned int hexaColorCode = 0x000000,
				const float scale = 1.);
  /*
  ** Texture methods
  */
  virtual void	        setTextureAt(const std::string &path,
				     const float x, const float y,
				     const float scale = 1.);
  virtual void	        fillRec(const unsigned int x,
				const unsigned int y,
				const unsigned int i,
				const unsigned int j,
				const unsigned int hexaColorCode = 0x000000,
				const unsigned int alpha = 255);

private:
  sf::RenderWindow	_window;
  sf::Font		_font;
  sf::Text		_text;
  sf::Sprite		_sprite;
  TextureManager	_manager;
  const int		_winX;
  const int		_winY;
  IGui::Key		_current_key;
  std::map<sf::Keyboard::Key, IGui::Key> _key_map;
  sf::Mouse		_mouse;

};

#endif		/* __MSFML__WINDOW__HPP__ */
