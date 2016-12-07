//
// Bitboard.cpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/tmp
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec  6 18:35:55 2016 Thomas Billot
// Last update Tue Dec  6 19:45:54 2016 Thomas Billot
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
  if (convertToIndex(coord) > _boardSize)
    throw std::out_of_range("Error: Bad coordinates");
  if (!(caseState == _pawnColor ||
	caseState == CaseState::EMPTY))
    throw std::logic_error("Error: Bad state for this bitboard");
  if (caseState == _pawnColor)
    _bitboard[_boardWidth * coord.x + coord.y] = _pawnColor;
  else
    _bitboard[_boardWidth * coord.x + coord.y] = CaseState::EMPTY;
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
  return _boardWidth * coord.x + coord.y;
}

