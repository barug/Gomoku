//
// Bitboard.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/tmp
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec  6 18:35:55 2016 Thomas Billot
// Last update Wed Dec  7 10:39:47 2016 Thomas Billot
//

#include			<stdexcept>
#include			"Bitboard.hpp"

Bitboard::Bitboard(const Bitboard::CaseState &state) : _pawnColor(state) {}

Bitboard::~Bitboard() {}

void					Bitboard::reset()
{
  for (unsigned int i = 0; i < (Bitboard::_boardSize - 1); i++)
    _bitboard.set(i,false);
}

void					Bitboard::setCaseAt(const Bitboard::Coordinates &coord,
					    const Bitboard::CaseState &caseState)
{
  int					index = convertToIndex(coord);
  
  if (index > _boardSize)
    throw std::out_of_range("Error: Bad coordinates");
  if (!(caseState == _pawnColor ||
	caseState == CaseState::EMPTY))
    throw std::logic_error("Error: Bad state for this bitboard");
  if (caseState == _pawnColor)
    _bitboard[index] = _pawnColor;
  else
    _bitboard[index] = CaseState::EMPTY;
  return;
}

const Bitboard::CaseState	        Bitboard::getCaseAt(const Bitboard::Coordinates &coord)
{
  int					index = convertToIndex(coord);
  
  if (index > _boardSize)
    throw std::out_of_range("Error: Bad coordinates");
  if (_bitboard[index] == _pawnColor)
    return _pawnColor;
  return CaseState::EMPTY;
}

int					Bitboard::convertToIndex(const Bitboard::Coordinates &coord)
{
  return _boardWidth * coord.y + coord.x;
}

#include <iostream>
#include <memory>

const std::bitset<Bitboard::_boardSize>	&Bitboard::getBitboard() const
{
  std::unique_ptr<std::bitset<Bitboard::_boardSize>>	bitset(new std::bitset<Bitboard::_boardSize>());
  int					j = 0;

  for (unsigned int i = _boardSize - 1; i > 0; i--)
    (*bitset)[j++] = _bitboard[i];
  return _bitboard;
}
