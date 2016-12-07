//
// main.cpp for onsenfout in /home/mikaz3/Tek3/B5/AI/Gomoku/tmp
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec  6 17:13:26 2016 Thomas Billot
// Last update Wed Dec  7 10:40:04 2016 Thomas Billot
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
#include	<cassert>
#include	"Bitboard.hpp"

int		testAlignementInDirection(std::bitset<NBR_BITSET> map, int index, int dir)
{
  int		count = 0;
  std::bitset<NBR_BITSET>	bitset = map;

  bitset <<= index;
  for (unsigned int i = 0; i <= 5; i++)
    {
      if (bitset.test(NBR_BITSET - 1) != true)
	break;
      count++;
      bitset <<= dir;
    }
  return count;
}

int		main()
{
  Bitboard	white(Bitboard::CaseState::WHITE);


  std::cout << "__\tUnitTests for Bitboard Class\t__" << std::endl;
  std::cout << "SetCaseAt 1,1 [WHITE]:";
  white.setCaseAt(Bitboard::Coordinates(1, 1), Bitboard::CaseState::WHITE);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 1)) == 1);
  std::cout << "\t OK!" << std::endl;
  std::cout << "SetCaseAt 1,2 [WHITE]:";
  white.setCaseAt(Bitboard::Coordinates(1, 2), Bitboard::CaseState::WHITE);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 2)) == 1);
  std::cout << "\t OK!" << std::endl;
  std::cout << "SetCaseAt 1,3 [WHITE]:";
  white.setCaseAt(Bitboard::Coordinates(1, 3), Bitboard::CaseState::WHITE);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 3)) == 1);
  std::cout << "\t OK!" << std::endl;
  std::cout << "SetCaseAt 1,4 [WHITE]:";
  white.setCaseAt(Bitboard::Coordinates(1, 4), Bitboard::CaseState::WHITE);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 4)) == 1);
  std::cout << "\t OK!" << std::endl;
  std::cout << "__\tBitboard Data\t__" << std::endl;
  std::cout << white.getBitboard() << std::endl;
  std::cout << "__\tTest Alignement\t__" << std::endl;
  std::cout << testAlignementInDirection(white.getBitboard(), 20, S) << std::endl;
  std::cout << "SetCaseAt 1,1 [EMPTY]:";
  white.setCaseAt(Bitboard::Coordinates(1, 1), Bitboard::CaseState::EMPTY);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 1)) == 0);
  std::cout << "\t OK!" << std::endl;
  std::cout << "SetCaseAt 1,2 [EMPTY]:";
  white.setCaseAt(Bitboard::Coordinates(1, 2), Bitboard::CaseState::EMPTY);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 2)) == 0);
  std::cout << "\t OK!" << std::endl;
  std::cout << "SetCaseAt 1,3 [EMPTY]:";
  white.setCaseAt(Bitboard::Coordinates(1, 3), Bitboard::CaseState::EMPTY);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 3)) == 0);
  std::cout << "\t OK!" << std::endl;
  std::cout << "SetCaseAt 1,4 [EMPTY]:";
  white.setCaseAt(Bitboard::Coordinates(1, 4), Bitboard::CaseState::EMPTY);
  assert(white.getCaseAt(Bitboard::Coordinates(1, 4)) == 0);
  std::cout << "\t OK!" << std::endl;
  std::cout << "__\tBitboard Data\t__" << std::endl;
  std::cout << white.getBitboard() << std::endl;
  return 0;
}
    
