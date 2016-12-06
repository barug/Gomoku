//
// Timer.cpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/includes
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Tue Dec  6 02:15:46 2016 bogard_t
// Last update Tue Dec  6 02:17:08 2016 bogard_t
//

# include	"Timer.hpp"

Timer::Timer() : _timerState(NONE)
{
}

Timer::~Timer()
{
}

void			Timer::setState(const Timer::State& timerState)
{
  _timerState = timerState;
}

const Timer::State&	Timer::getState() const
{
  return (_timerState);
}

unsigned int		Timer::timeLeft()
{
  return (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastTick).count());
}

bool			Timer::currentTimer(const unsigned int timer)
{
  if (_timerState == Timer::State::TIMER_OUT)
    return (false);
  if (_timerState == Timer::State::NONE)
    _lastTick = std::chrono::system_clock::now();
  _now = std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastTick).count() > timer)
    {
      _lastTick = _now;
      _timerState = Timer::State::TIMER_OUT;
      return (false);
    }
  else
    {
      _timerState = Timer::State::TIMER_IN;
      return (true);
    }
}
