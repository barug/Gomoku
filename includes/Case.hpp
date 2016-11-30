//
// Case.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 12:57:36 2016 bogard_t
// Last update Wed Nov 30 12:58:54 2016 bogard_t
//

#ifndef			__CASE_HPP__
# define		__CASE_HPP__

class Case
{
public:
  Case();
  Case(const unsigned int x, const unsigned int y,
       const unsigned int xPixel, const unsigned int yPixel);
  ~Case();

  enum ColorSlot
    {
      NONE = 0,
      BLACK = 1,
      WHITE = 2
    };

  unsigned int		getX() const;
  unsigned int		getY() const;
  unsigned int		getXPixel() const;
  unsigned int		getYPixel() const;
  void			setColorSlot(const ColorSlot slot);
  ColorSlot		getColorSlot() const;

private:
  unsigned int		_x;
  unsigned int		_y;
  unsigned int		_xPixel;
  unsigned int		_yPixel;
  ColorSlot		_colorSlot;
};

#endif			// __CASE_HPP__
