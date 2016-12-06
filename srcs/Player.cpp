//
// Player.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/includes
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Thu Dec  1 14:55:35 2016 bogard_t
// Last update Tue Dec  6 16:37:06 2016 bogard_t
//

# include		"Player.hpp"

Player::Player(const Player::Type &type) : _type(type), _score(0)
{
}

Player::~Player()
{
}

unsigned int	Player::getScore() const
{
  return _score;
}

void		Player::setScore(const unsigned int score)
{
  _score = score;
}

void		Player::setType(const Player::Type type)
{
  _type = type;
}

Player::Type	Player::getType() const
{
  return _type;
}

const Player&	Player::operator=(const Player::Type type)
{
  _type = type;
  return (*this);
}
