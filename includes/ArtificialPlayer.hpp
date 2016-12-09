
#ifndef _MINMAX_PLAYER_HPP_
# define _MINMAX_PLAYER_HPP_

# include <memory>
# include "IPlayer.hpp"
# include "Map.hpp"
# include "IArtificialInteligence.hpp"

class						ArtificialPlayer : public IPlayer
{
private:
  std::unique_ptr<IArtificialInteligence>	_AI;
  const Map					&_map;
  unsigned int					_score;
  Map::CaseState				_color;
  
public:
  ArtificialPlayer(IArtificialInteligence *AI,
		   const Map &map,
		   Map::CaseState color);
  virtual ~ArtificialPlayer();
  virtual IPlayer::Type		getType();
  virtual Map::Coordinates	*getNextAction();
  virtual void			setScore(unsigned int score);
  virtual unsigned int		getScore();
  virtual Map::CaseState	getColor();
};

#endif /* !_MINMAX_PLAYER_HPP_ */
