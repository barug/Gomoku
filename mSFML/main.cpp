# include "mSFML_Window.hpp"

int             main(int, char *[])
{
  IGui          *gui = new mSFML_Window("msfml test window", 800, 600);

  while (gui->isAlive())
    {
      gui->clear();
      gui->handleEvents();
      gui->display();
    }
  return (0);
}
