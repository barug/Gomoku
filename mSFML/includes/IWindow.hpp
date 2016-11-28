//
// IWindow.hpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 16 16:16:14 2016 Thomas Billot
// Last update Mon Nov 28 17:02:39 2016 bogard_t
//

#ifndef			__IWINDOW__HPP__
# define		__IWINDOW__HPP__

# define		DEFAULT_WINDOW_X (800)
# define		DEFAULT_WINDOW_Y (600)
# define		DEFAULT_WINDOW_NAME ("This is a mSFML demo")

class		IWindow
{

public:

    enum Key : unsigned int
    {
      NONE = 0,
      ENTER,
      SPACE,
      RIGHT,
      LEFT,
      DOWN,
      UP,
      K_1,
      K_2,
      K_3,
      K_4,
      K_5,
      K_6,
      K_7,
      K_8,
      K_9,
      K_0,
      K_Z,
      K_Q,
      K_S,
      K_D
    };

  /*
  ** Dtor
  */

  virtual ~IWindow() {}

  /** Public Member Functions **/

  /*
  ** Windows methods
  */
  virtual void		update(void) = 0;
  virtual void		display(void) = 0;
  virtual void		clear(void) = 0;
  virtual bool		isAlive(void) = 0;
  virtual IWindow::Key 	getKey(void) const = 0;
  virtual void	       	handleEvents(void) = 0;

  /*
  ** Font methods
  */
  virtual void		loadFont(const std::string &path) = 0;
  virtual void		writeAt(const std::string &msg,
				const float x, const float y,
				const float size) = 0;

  /*
  ** Font methods
  */
  virtual void	        setTextureAt(const std::string &path,
				     const float x, const float y) = 0;
};

#endif			/* __IWINDOW__HPP__ */
