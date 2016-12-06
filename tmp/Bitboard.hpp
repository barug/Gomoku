//
// Bitboard.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/tmp
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec  6 18:17:25 2016 Thomas Billot
// Last update Tue Dec  6 19:30:29 2016 Thomas Billot
//

#pragma once

#include				<bitset>

class					Bitboard
{
  
public:

  enum					CaseState : char
    {
      EMPTY,
      WHITE,
      BLACK
    };
  
  struct				Coordinates
  {
    
    int					_x;
    int					_y;
    
  public:
    
    Coordinates(const unsigned int x, const unsigned int y);
    Coordinates operator+(const Bitboard::Coordinates &rhs);
    Coordinates operator-(const Bitboard::Coordinates &rhs);
    bool	operator==(const Bitboard::Coordinates &rhs);
    int					x() const;
    int					y() const;
    
  };
  
public:

  explicit				Bitboard(const Bitboard::CaseState &state);
  ~Bitboard();

  void					reset();
  void					setCaseAt(const Bitboard::Coordinates &coordinates,
						  const Bitboard::CaseState &caseState);
  const Bitboard::CaseState	        getCaseAt(const Bitboard::Coordinates &coordinates);
  const Bitboard::CaseState	        &getCaseAtIndex(const int index);
  int					convertToIndex(const Bitboard::Coordinates &coordinates);
  
private:

  Bitboard::CaseState			_pawnColor;
  static const int			_boardWidth = 19;
  static const int			_boardSize = _boardWidth * _boardWidth;
  std::bitset<_boardSize>		_bitboard;
  
  Bitboard(const Bitboard &);
  const Bitboard			&operator=(const Bitboard &);
};
