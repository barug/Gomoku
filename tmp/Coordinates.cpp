//
// Coordinates.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/tmp
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec  6 19:08:55 2016 Thomas Billot
// Last update Tue Dec  6 19:10:56 2016 Thomas Billot
//

#include		"Bitboard.hpp"

Bitboard::Coordinates::Coordinates(const unsigned int x,
			      const unsigned int y)
  : _x(x),
    _y(y)
{}

int				Bitboard::Coordinates::x() const
{
  return _x;
}

int				Bitboard::Coordinates::y() const
{
  return _y;
}

Bitboard::Coordinates		Bitboard::Coordinates::operator+(const Bitboard::Coordinates &rhs)
{
  return Coordinates(_x + rhs.x(), _y + rhs.y());
}

Bitboard::Coordinates	        Bitboard::Coordinates::operator-(const Bitboard::Coordinates &rhs)
{
  return Coordinates(_x - rhs.x(), _y - rhs.y());
}

bool				Bitboard::Coordinates::operator==(const Bitboard::Coordinates &rhs)
{
  return _x == rhs.x() && _y == rhs.y();
}
