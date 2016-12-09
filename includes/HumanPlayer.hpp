
#ifndef _HUMAN_PLAYER_HPP_
# define _HUMAN_PLAYER_HPP_

# include "IPlayer.hpp"
# include "GomokuUI.hpp"

class				HumanPlayer : public IPlayer
{

  GomokuUI		&_gomokuUI;
  unsigned int			_score;
  Map::CaseState		_color;
  
public:
  HumanPlayer(GomokuUI &gomokuUI, Map::CaseState color);
  virtual ~HumanPlayer();
  virtual IPlayer::Type		getType();
  virtual Map::Coordinates	*getNextAction();
  virtual void			setScore(unsigned int score);
  virtual unsigned int		getScore();
  virtual Map::CaseState	getColor();
};

#endif /* _HUMAN_PLAYER_HPP_ */
