#ifndef GOMOKU_MAP_HPP
# define GOMOKU_MAP_HPP

# include <vector>

# define MAP_WIDTH			(19)
# define MAP_SIZE			(MAP_WIDTH * MAP_WIDTH)

class					Map
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

private:
  std::vector<Map::CaseState>		_mapData;

public:
  Map();
  ~Map();

  void					resetAllCases(const unsigned int size);
  void					setCaseAt(const Map::Coordinates &coordinates,
						  const Map::CaseState &state);
  const Map::CaseState			&getCaseAt(const Map::Coordinates &coordinates);
  const Map::CaseState			&getCaseAtIndex(const int index);
  const std::vector<Map::CaseState>	&getMapData();
};

#endif /* GOMOKU_MAP_HPP */
