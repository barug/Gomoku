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

private:
  std::vector<char>		_mapData;

public:
  Map();
  Map(std::vector<char> &mapData);
  ~Map();

  void				resetAllCases(const unsigned int size);
  void				setCaseAt(const Map::Coordinates &coordinates,
					  const Map::CaseState &state);
  const char			&getCaseAt(const Map::Coordinates &coordinates) const;
  const char			&getCaseAtIndex(const int index) const;
  void				setCaseAtIndex(int index, Map::CaseState state);
  const std::vector<char>	&getMapData() const;
  void			        mapDump() const;
};

#endif /* GOMOKU_MAP_HPP */
