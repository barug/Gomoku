//
// main.cpp for onsenfout in /home/mikaz3/Tek3/B5/AI/Gomoku/tmp
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec  6 17:13:26 2016 Thomas Billot
// Last update Tue Dec  6 19:33:56 2016 Thomas Billot
//

# define	NBR_BITSET	(19 * 19)
# define        NW		(20)
# define	NE		(-20)
# define	E		(+1)
# define	W		(-1)
# define	S		(19)

#include	<bitset>
#include	<iostream>
#include	<vector>
#include	"Bitboard.hpp"

int		testAlignementInDirection(std::bitset<NBR_BITSET> map, int index, int dir)
{
  int		count = 0;
  std::bitset<NBR_BITSET>	bitset = map;

  bitset <<= index;
  for (unsigned int i = 0; i <= 5; i++)
    {
      std::cout << "CUR= " << bitset << std::endl;
      if (bitset.test(NBR_BITSET - 1) != true)
	break;
      count++;
      bitset <<= dir;
    }
  return count;
}

int		main()
{
  std::string	map("1100000000000000000001000000000000000000010000000000000000000100000000000000001000000000000000001000000000000000000100000000000000000010000000000000000001000000000000000000100000000000000000010000000000000000001000000000000000000100000000000000000010000000000000000001000000000000000000100000000000000000010000000000000000001000000000000000000100000000000000000");
  std::string	map1("01110000000000000000010000000000000000000100000000000000000001000000000000000010000000000000000");
  std::bitset<NBR_BITSET> bitset(map);

  Bitboard	white(Bitboard::CaseState::WHITE);

  Bitboard::Coordinates		coord(1, 1);
  
  white.setCaseAt(coord, Bitboard::CaseState::EMPTY);
  std::cout << white.getCaseAt(coord) << std::endl;
  std::cout << "MAP = " << bitset << std::endl;
  std::cout << "Count = " << testAlignementInDirection(bitset, 1, W) << std::endl;
  return 0;
}
    
