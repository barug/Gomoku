#ifndef GOMOKU_MAP_HPP
# define GOMOKU_MAP_HPP

# include <bitset>
# include <vector>

# define MAP_WIDTH			(19)
# define MAP_SIZE			(MAP_WIDTH * MAP_WIDTH)

class					Map
{
public:
  enum					CaseState : char
    {
      EMPTY				= 0,
      WHITE				= 1,
      BLACK				= 2
    };

  struct				Coordinates
  {
  public:
    Coordinates(const unsigned int x, const unsigned int y);
    Coordinates operator+(const Map::Coordinates &rhs);
    Coordinates operator-(const Map::Coordinates &rhs);
    bool	operator==(const Map::Coordinates &rhs);
    int					getX() const;
    int					getY() const;
    int					x;
    int					y;
  };

  static const int		boardWidth = 19;
  static const int		boardSize = boardWidth * boardWidth;
  
private:
  std::bitset<boardSize>	_whiteBoard;
  std::bitset<boardSize>	_blackBoard;

public:
  Map();
  Map(Map &map);
  ~Map();

  void				resetAllCases();
  void				setCaseAt(const Map::Coordinates &coordinates,
					  const Map::CaseState &state);
  Map::CaseState		getCaseAt(const Map::Coordinates &coordinates) const;
  Map::CaseState		getCaseAtIndex(const int index) const;
  void				setCaseAtIndex(int index, Map::CaseState state);
  int				convertToIndex(const Map::Coordinates &coordinates) const;
  const std::vector<char>	&getMapData() const;
  void			        mapDump() const;
};

#endif /* GOMOKU_MAP_HPP */
