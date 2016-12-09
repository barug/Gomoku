
#ifndef MIN_MAX_HPP
# define MIN_MAX_HPP

# include "IArtificialInteligence.hpp"
# include "GomokuReferee.hpp"

# define RECURSION_DEPTH	(3)

class				GomokuMinMax
{
  enum				turn : unsigned char
    {
      MIN,
      MAX
    };
    
    struct Result
    {
      Result();
      Result(unsigned int x,
	     unsigned int y,
	     int actionScore);
      Map::Coordinates			coordinates;
      int				actionScore;
    };

  Map::CaseState			_iaColor;
  Map::CaseState			_enemyColor;
  int					_alpha;

public:
  unsigned int			calculateActionScore(const Map &map,
						     Map::Coordinates Action,
						     Map::CaseState color);
  GomokuMinMax::Result		_minMax(const Map &map,
					unsigned int depth,
					int alpha,
					int beta,
					GomokuMinMax::turn turn,
				        int actionsScore);
  
public:
  GomokuMinMax();
  virtual Map::Coordinates	computeNextAction(const Map &map);
};

#endif /* MIN_MAX_HPP */
