//
// GomokuUI.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Tue Dec  6 02:06:57 2016 bogard_t
// Last update Sat Dec 10 18:24:32 2016 bogard_t
//

#ifndef	        __GOMOKU_UI_HPP__
# define	__GOMOKU_UI_HPP__

# include	"Map.hpp"
# include	"IGui.hpp"
# include	"Timer.hpp"
# include	"IPlayer.hpp"

class	        GomokuUI
{
public:
  enum		Context
    {
      START_SCREEN = 0,
      WAITING = 1,
      GAME = 2,
      MENU = 3,
      WIN_SCREEN = 4
    };

  explicit GomokuUI(IGui &gui, Map &map);
  ~GomokuUI();

  void				        displayUI(const unsigned int scoreJ1,
						  const unsigned int scoreJ2,
						  const unsigned int captureJ1,
						  const unsigned int captureJ2);
  void					displayWinScreen(const std::string &msg);

  void					displayMenu(void);
  void				        displayWaiting(void);
  IPlayer::Type				displayStartScreen(void);
  void					displayGame(void);
  void				        updateMap(void);

  bool					getClicked(void) const;
  Map::Coordinates*			getClickedTile(void);

  void					setContext(const GomokuUI::Context context);
  GomokuUI::Context			getContext(void) const;

private:
  IGui					&_gui;
  Map					&_map;
  std::unique_ptr<Timer>	        _timer;
  GomokuUI::Context			_context;
  bool					_restart;
};

#endif		// __GOMOKU_UI_HPP__
