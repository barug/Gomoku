//
// GomokuUI.hpp for Gomoku in /home/bogard_t/rendu/tek3/Gomoku/srcs
//
// Made by bogard_t
// Login   <bogard_t@epitech.net>
//
// Started on  Tue Dec  6 02:06:57 2016 bogard_t
// Last update Tue Dec  6 14:29:28 2016 bogard_t
//

#ifndef	        __GOMOKU_UI_HPP__
# define	__GOMOKU_UI_HPP__

# include	"Map.hpp"
# include	"IGui.hpp"
# include	"Timer.hpp"
# include	"Player.hpp"

class	        GomokuUI
{
public:
  enum		Context
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
  void					displayStartScreen(Player &player2);
  void					displayGame();
  void				        updateMap();

  bool					getClicked() const;
  Map::Coordinates*			getClickedTile();

  void					setContext(const GomokuUI::Context context);
  GomokuUI::Context			getContext() const;

private:
  IGui					&_gui;
  Map					&_map;
  std::unique_ptr<Timer>	        _timer;
  GomokuUI::Context			_context;
  bool					_restart;
};

#endif		// __GOMOKU_UI_HPP__
