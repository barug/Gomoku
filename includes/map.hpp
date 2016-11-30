#ifndef GOMOKU_MAP_HPP
# define GOMOKU_MAP_HPP

# include <vector>

# define MAP_WIDTH	(19)
# define MAP_SIZE	(MAP_WIDTH * MAP_WIDTH)

class			Map
{
public:
  enum			CaseState
    {
      EMPTY,
      WHITE,
      BLACK
    };

private:
  std::vector<char>	_mapData;
  
public:
  Map();
  ~Map();

  void				setCaseAt(const unsigned int &x,
					  const unsigned int &y,
					  const Map::CaseState &state);
  const Map::CaseState		&getCaseAt(const unsigned int &x,
					   const unsigned int &y);
  const std::vector<char>	&getMapData();
};

#endif /* GOMOKU_MAP_HPP */
