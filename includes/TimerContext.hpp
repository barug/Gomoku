#ifndef		_TIMER_CONTEXT_HPP_
# define	_TIMER_CONTEXT_HPP_

# include	<memory>
# include	<chrono>

class		TimerContext
{
public:
  TimerContext() : _timerState(NONE),
		   _currentTimer(NONE)
  {}
  ~TimerContext() {};

  enum		State
    {
      NONE = 0,
      PUSHED = 1,
      TIMER_IN = 2,
      TIMER_OUT = 3,
      OFF = 4
    };

  void		setState(const State& timerState)
  {
    _currentTimer = timerState;
  }

  const State	&getState() const
  {
    return (_currentTimer);
  }

private:
  std::chrono::system_clock::time_point _lastTick;
  std::chrono::system_clock::time_point	_now;
  State					_timerState;
  State					_currentTimer;
};

#endif		// _TIMER_CONTEXT_HPP_
