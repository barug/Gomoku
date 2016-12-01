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
    int					x;
    int					y;
  };

private:
  std::vector<Map::CaseState>		_mapData;
  
public:
  Map();
  ~Map();

  void					setCaseAt(const Map::Coordinates &coordinates,
						  const Map::CaseState &state);
  const Map::CaseState			&getCaseAt(const Map::Coordinates &coordinates);
  const std::vector<Map::CaseState>	&getMapData();
};

#endif /* GOMOKU_MAP_HPP */
