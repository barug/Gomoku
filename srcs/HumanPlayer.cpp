
#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(GomokuUI &gomokuUI, Map::CaseState color)
  : _gomokuUI(gomokuUI),
    _score(0),
    _color(color)
{}

HumanPlayer::~HumanPlayer()
{}

IPlayer::Type		HumanPlayer::getType()
{
  return IPlayer::HUMAN;
}

Map::Coordinates	*HumanPlayer::getNextAction()
{
  return _gomokuUI.getClickedTile();
}

void			HumanPlayer::setScore(unsigned int score)
{
  _score = score;
}

unsigned int		HumanPlayer::getScore()
{
  return _score;
}

Map::CaseState		HumanPlayer::getColor()
{
  return _color;
}
