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

  static const int 			offsetX = 30;
  static const int			offsetY = 30;
  static const int			offsetMapX = 230;
  static const int			offsetMapY = 20;
  static const int			mapSize = 19;

private:
  std::vector<Map::CaseState>		_mapData;

public:
  Map();
  ~Map();

  void					setCaseAt(const unsigned int &x,
						  const unsigned int &y,
						  const Map::CaseState &state);
  const Map::CaseState			&getCaseAt(const unsigned int &x,
						   const unsigned int &y);
  const std::vector<Map::CaseState>	&getMapData();
};

#endif /* GOMOKU_MAP_HPP */
