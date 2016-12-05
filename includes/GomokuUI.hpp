#ifndef					__GOMOKU_UI_HPP__
# define				__GOMOKU_UI_HPP__

# include				"Map.hpp"
# include				"IGui.hpp"
# include				"TimerContext.hpp"
# include				"Player.hpp"

class					GomokuUI
{
public:
  enum					Context
    {
      STARTSCREEN = 0,
      WAITING = 1,
      GAME = 2,
      MENU = 3
    };

					GomokuUI(IGui &gui, Map &map);
					~GomokuUI();


  void					displayMenu();
  void				        displayWaiting();
  void					displayStartScreen();

  void				        updateMap();

  bool					currentTimer(const unsigned int timer);
  bool					getClicked();
  Map::Coordinates*			getClickedOnTile();

  void					setContext(GomokuUI::Context context);
  GomokuUI::Context			getContext() const;

  bool					magnetTile(const unsigned int mouseX,
						   const unsigned int mouseY,
						   const unsigned int x,
						   const unsigned int y,
						   const unsigned int intensityX = 13,
						   const unsigned int intensityY = 13) const;

private:
  // static const int			timerWaiting = 700;
  // static const int			timerCurrent = 200;
  IGui					&_gui;
  Map					&_map;
  GomokuUI::Context			_context;
  TimerContext				_currentTimer;
  std::chrono::system_clock::time_point _lastTick;
  std::chrono::system_clock::time_point	_now;
};

#endif					// __GOMOKU_UI_HPP__
