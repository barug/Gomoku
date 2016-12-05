//
// IGui.hpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 16 16:16:14 2016 Thomas Billot
// Last update Sun Dec  4 18:17:48 2016 bogard_t
//

#ifndef			__IGUI__HPP__
# define		__IGUI__HPP__

# define		DEFAULT_WINDOW_X (800)
# define		DEFAULT_WINDOW_Y (600)
# define		DEFAULT_WINDOW_NAME ("This is a mSFML demo")

# include		<string>
# include		<vector>

class		IGui
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
      K_D,
      K_W
    };

  static const int 	offsetX = 30;
  static const int	offsetY = 30;
  static const int	offsetMapX = 230;
  static const int	offsetMapY = 20;
  static const int	mapSize = 19;

  /*
  ** Dtor
  */

  virtual ~IGui() {}

  /** Public Member Functions **/

  /*
  ** Windows methods
  */
  virtual void		update(void) = 0;
  virtual void		display(void) = 0;
  virtual void		clear(void) = 0;
  virtual bool		isAlive(void) = 0;

  /*
  ** Keyboard Events methods
  */
  virtual IGui::Key 	getKey(void) const = 0;
  virtual void	       	handleEvents(void) = 0;

  /*
  ** Mouse Event
  */
  virtual unsigned int	getMouseX(void) const = 0;
  virtual unsigned int	getMouseY(void) const = 0;
  virtual bool		buttonLeftIsClicked(void) const = 0;
  virtual bool		buttonRightIsClicked(void) const = 0;

  /*
  ** Font methods
  */
  virtual void		loadFont(const std::string &path) = 0;
  virtual void	        writeAt(const std::string  &msg,
				const float x, const float y,
				const unsigned int hexaColorCode = 0x000000,
				const float scale = 1.) = 0;

  /*
  ** Texture methods
  */
  virtual void	        setTextureAt(const std::string &path,
				     const float x, const float y,
				     const float scale = 1.) = 0;
  virtual void	        fillRec(const unsigned int x,
				const unsigned int y,
				const unsigned int i,
				const unsigned int j,
				const unsigned int hexaColorCode = 0x000000,
				const unsigned int alpha = 255) = 0;
  virtual void	        fillCircle(const unsigned int x,
				   const unsigned int y,
				   const unsigned int i,
				   const unsigned int j,
				   const unsigned int hexaColorCode = 0x000000) = 0;

  /*
  ** Color converter
  */
  inline const std::vector<unsigned int> hexaToRgb(const unsigned int hexcode)
  {
    const std::vector<unsigned int> rgb =
      {
	(hexcode >> 16) & 0xFF,
	(hexcode >> 8) & 0xFF,
	(hexcode & 0xFF)
      };
    return (rgb);
  }

  inline unsigned int			rgbToHexa(const unsigned int r,
						  const unsigned int g,
						  const unsigned int b)
  {
    return ((r << 16) + (g << 8) + b);
  }

};

#endif			/* __IWINDOW__HPP__ */
