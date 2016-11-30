//
// Case.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/mSFML/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Nov 30 12:56:10 2016 bogard_t
// Last update Wed Nov 30 13:00:58 2016 bogard_t
//

# include		"Case.hpp"

Case::Case() : _colorSlot(NONE) {}
Case::Case(const unsigned int x, const unsigned int y,
	   const unsigned int xPixel, const unsigned int yPixel) : _x(x),
								   _y(y),
								   _xPixel(xPixel),
								   _yPixel(yPixel),
								   _colorSlot(NONE)
{
}

Case::~Case() {}

unsigned int		Case::getX() const
{
  return (_x);
}

unsigned int		Case::getY() const
{
  return (_y);
}

unsigned int		Case::getXPixel() const
{
  return (_xPixel);
}

unsigned int		Case::getYPixel() const
{
  return (_yPixel);
}

void			Case::setColorSlot(const ColorSlot slot)
{
  _colorSlot = slot;
}

Case::ColorSlot		Case::getColorSlot() const
{
  return (_colorSlot);
}
