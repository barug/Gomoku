//
// Timer.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/includes
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Tue Dec  6 02:15:39 2016 bogard_t
// Last update Tue Dec  6 02:20:41 2016 bogard_t
//

#ifndef		_TIMER_HPP_
# define	_TIMER_HPP_

# include	<memory>
# include	<chrono>

class		Timer
{
public:
  Timer();
  ~Timer();

  enum		State
    {
      NONE = 0,
      TIMER_IN = 1,
      TIMER_OUT = 2
    };

  void					setState(const Timer::State& timerState);
  const Timer::State&			getState() const;
  unsigned int				timeLeft();
  bool				        currentTimer(const unsigned int timer);

private:
  std::chrono::system_clock::time_point _lastTick;
  std::chrono::system_clock::time_point	_now;
  State					_timerState;
};

#endif		// _TIMER_HPP_
