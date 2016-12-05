#ifndef		_TIMER_CONTEXT_HPP_
# define	_TIMER_CONTEXT_HPP_

class		TimerContext
{
public:
  TimerContext() : _timerState(NONE) {}
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
    _timerState = timerState;
  }

  const State	&getState() const
  {
    return (_timerState);
  }

private:
  State		_timerState;
};

#endif		// _TIMER_CONTEXT_HPP_
