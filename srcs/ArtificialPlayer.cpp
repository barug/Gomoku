
#include "ArtificialPlayer.hpp"

ArtificialPlayer::ArtificialPlayer(IArtificialInteligence *AI,
		 const Map &map,
		 Map::CaseState color)
  : _AI(AI),
    _map(map),
    _score(0),
    _color(color)
{}

ArtificialPlayer::~ArtificialPlayer()
{}

IPlayer::Type		ArtificialPlayer::getType()
{
  return IPlayer::AI;
}

Map::Coordinates	*ArtificialPlayer::getNextAction()
{
  return _AI->computeNextAction(_map);
}

void			ArtificialPlayer::setScore(unsigned int score)
{
  _score = score;
}
unsigned int		ArtificialPlayer::getScore()
{
  return _score;
}

Map::CaseState		ArtificialPlayer::getColor()
{
  return _color;
}
