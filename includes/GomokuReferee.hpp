//
// Referee.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku/mSFML/includes
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 30 12:23:53 2016 Thomas Billot
// Last update Fri Dec  9 14:35:19 2016 Josselin
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
  Map				_map;
  int				_whiteCapturedPieces;
  int				_blackCapturedPieces;

public:
  explicit			GomokuReferee(Map &map);
  virtual			~GomokuReferee();

  virtual IReferee::gameState	validatePlayerAction(int CoordX, int CoordY, const bool turn);

  void				testCapture(Map &map, Map::Coordinates coordinates);
  void				testCaptureInDirection(GomokuReferee::Direction direction, Map &map, Map::Coordinates coordinates);
  bool				hasCapture(Map &map, Map::Coordinates coordinates, int xInc, int yInc);
  void				capturePieces(Map &map, Map::Coordinates coordinates, int xInc, int yInc);
  std::vector<int>		testAlignement(const Map &map, Map::Coordinates coordinates);
  int				testAlignementInDirection(GomokuReferee::Direction direction, const Map &map, Map::Coordinates coordinates);
  int				countAlignement(const Map &map, Map::Coordinates coordinates, int xInc, int yInc);
  bool				hasFiveInARow(GomokuReferee::Direction direction, Map &map, Map::Coordinates coordinates);
  bool				simulateCapture(Map &map, Map::Coordinates coordinates, Map::CaseState rivals, int xInc, int yInc, int xIncBack, int yIncBack, int i);
  void				initIncDirection(GomokuReferee::Direction direction, int &xInc, int &yInc);
  GomokuReferee::Direction	invertDirection(GomokuReferee::Direction direction);
  int				getWhiteCapturedPieces();
  int				getBlackCapturedPieces();


};

int			testAlignementInDirection(GomokuReferee::Direction direction,
						  const Map &map,
						  Map::Coordinates coordinates,
						  Map::CaseState color);
bool			testCaptureInDirection(GomokuReferee::Direction direction,
					       const Map &map,
					       Map::Coordinates coordinates);


#endif			/* _GOMOKUREFEREE_HPP_ */
