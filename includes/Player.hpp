//
// Player.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/includes
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Thu Dec  1 14:55:46 2016 bogard_t
// Last update Tue Dec  6 16:36:42 2016 bogard_t
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

  Player(const Player::Type &type = HUMAN);
  ~Player();

  void		setScore(const unsigned int score);
  unsigned int	getScore() const;

  void		setType(const Player::Type type);
  Player::Type	getType() const;
  const Player&	operator=(const Player::Type type);

private:
  Player::Type	_type;
  unsigned int	_score;
};

#endif		// __PLAYER_HPP__
