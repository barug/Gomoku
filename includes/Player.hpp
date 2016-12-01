//
// Player.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/includes
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Thu Dec  1 14:55:46 2016 bogard_t
// Last update Thu Dec  1 15:12:06 2016 bogard_t
//

#ifndef		__PLAYER_HPP__
# define       	__PLAYER_HPP__

class		Player
{
public:

  enum Type
    {
      HUMAN = 0,
      AI = 1
    };

  Player(const Type type);
  ~Player();

  void		setScore(const unsigned int score);
  unsigned int	getScore() const;

  void		setType(const Player::Type type);
  Player::Type	getType() const;

private:
  Player::Type	_type;
  unsigned int	_score;

};

#endif		// __PLAYER_HPP__