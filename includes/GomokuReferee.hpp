//
// Referee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:23:53 2016 Thomas Billot
// Last update Sun Dec 11 17:46:41 2016 Thomas Billot
//

#ifndef			_GOMOKUREFEREE_HPP_
# define		_GOMOKUREFEREE_HPP_

# include		"Map.hpp"
# include		"IReferee.hpp"

class			GomokuReferee : public IReferee
{
public:

  enum			Direction
    {
      NORTH		= -19,
      NORTH_EAST	= -18,
      EAST		= 1,
      SOUTH_EAST	= 20,
      SOUTH		= 19,
      SOUTH_WEST	= 18,
      WEST		= -1,
      NORTH_WEST	= -20,
    };

   static constexpr GomokuReferee::Direction directions[8] = {NORTH,
							      NORTH_EAST,
							      EAST,
							      SOUTH_EAST,
							      SOUTH,
							      SOUTH_WEST,
							      WEST,
							      NORTH_WEST};

private:
  Map				&_map;
  int				_whiteCapturedPieces;
  int				_blackCapturedPieces;
  Map::CaseState		_pawnToCheck;
  Map::CaseState		_ennemyPawn;

public:
  explicit			GomokuReferee(Map &map);
  virtual			~GomokuReferee();

  virtual IReferee::GameState	validatePlayerAction(int CoordX, int CoordY, const bool turn);
  virtual void			resetReferee();
  virtual int			getP1Score();
  virtual int			getP2Score();

private:
  void				setTurn(int CoordX, int CoordY, const bool turn);
  bool				testDoubleThree(Map::Coordinates coordinates);
  void				testCapture(Map::Coordinates coordinates);
  void				testCaptureInDirection(GomokuReferee::Direction direction, Map::Coordinates coordinates);
  bool				hasCapture(Map::Coordinates coordinates, int xInc, int yInc);
  void				capturePieces(Map::Coordinates coordinates, int xInc, int yInc);
  std::vector<int>		testAlignement(Map::Coordinates coordinates);
  int				testAlignementInDirection(GomokuReferee::Direction direction, Map::Coordinates coordinates);
  int				countAlignement(Map::Coordinates coordinates, int xInc, int yInc);
  bool				hasFiveInARow(GomokuReferee::Direction direction, Map::Coordinates coordinates);
  IReferee::GameState		TestFiveInARow(int CoordX, int CoordY, int i, const bool turn);
  bool				simulateCapture(Map::Coordinates coordinates, Map::CaseState rivals, int xInc, int yInc, int xIncBack, int yIncBack, int i);
  void				initIncDirection(GomokuReferee::Direction direction, int &xInc, int &yInc);
  GomokuReferee::Direction	invertDirection(GomokuReferee::Direction direction);
  bool				FindPattern3inLine(std::vector<Map::Coordinates> &v, Map::Coordinates coordinates);
  bool				FindPattern2inLine1Empty(std::vector<Map::Coordinates> &v, Map::Coordinates coordinates);
  bool				checkPattern1(Map::Coordinates c, Map::Coordinates d);
  bool				checkPattern2(Map::Coordinates c, Map::Coordinates d);
  Map::Coordinates		Pattern1(Map::Coordinates c);
  Map::Coordinates		Pattern2(Map::Coordinates c);
  bool				checkForEnnemyPawn(std::vector<Map::Coordinates> &v);
  int				getWhiteCapturedPieces();
  int				getBlackCapturedPieces();

};

int				testAlignementInDirection(GomokuReferee::Direction direction,
							  const Map &map,
							  Map::Coordinates coordinates,
							  Map::CaseState color);
bool				testCaptureInDirection(GomokuReferee::Direction direction,
						       const Map &map,
						       Map::Coordinates coordinates);


#endif			/* _GOMOKUREFEREE_HPP_ */
