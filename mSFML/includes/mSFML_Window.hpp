//
// mSFML_Window.hpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 16 17:07:01 2016 Thomas Billot
// Last update Mon Nov 28 17:02:25 2016 bogard_t
//

#ifndef		__MSFML__WINDOW__HPP__
# define	__MSFML__WINDOW__HPP__

# include	<SFML/Window.hpp>
# include	<SFML/Graphics.hpp>
# include	<SFML/Graphics/Font.hpp>

# include	"mSFML.hpp"
# include	"IWindow.hpp"
# include	"TextureManager.hpp"
// # include "SFML/String.hpp"
class		mSFML_Window : public IWindow
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
  virtual IWindow::Key	getKey(void) const;
  virtual void		handleEvents(void);
  virtual bool		isAlive(void);

  /*
  ** Font methods
  */
  virtual void		loadFont(const std::string &path);
  virtual void	        writeAt(const std::string  &msg,
				const float x, const float y,
				const float size);
  /*
  ** Texture methods
  */
  virtual void	        setTextureAt(const std::string &path,
				     const float x, const float y);

private:
  sf::RenderWindow	_window;
  sf::Font		_font;
  sf::Texture		_texture;
  sf::Text		_string;
  TextureManager	_manager;

  const int		_winX;
  const int		_winY;
  IWindow::Key		_current_key;

  std::map<sf::Keyboard::Key, IWindow::Key> _key_map;

  /*
  ** Private methods
  */
  bool			_keyPressed(sf::Event event);
  void			_keyReleased(sf::Event event);
};

#endif		/* __MSFML__WINDOW__HPP__ */
