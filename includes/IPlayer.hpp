
#ifndef _IPLAYER_HPP_
# define _IPLAYER_HPP_

# include "Map.hpp"

class				IPlayer
{
public:
  enum Type
    {
      HUMAN = 0,
      AI = 1,
      NONE = 2
    };

  virtual ~IPlayer() {}
  virtual IPlayer::Type		getType() = 0;
  virtual Map::Coordinates	*getNextAction() = 0;
  virtual void			setScore(unsigned int score) = 0;
  virtual unsigned int		getScore() = 0;
  virtual Map::CaseState	getColor() = 0;
};

#endif /* !_PLAYER_HPP */
