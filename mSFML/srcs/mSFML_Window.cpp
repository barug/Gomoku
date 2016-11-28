//
// mSFML_Window.cpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 16 17:14:22 2016 Thomas Billot
// Last update Mon Nov 28 17:24:12 2016 bogard_t
//

#include <iostream>
#include "mSFML_Window.hpp"

mSFML_Window::mSFML_Window(const std::string &windowName,
			   const int winX,
			   const int winY) : _window(),
					     _winX(winX),
					     _winY(winY),
					     _current_key(NONE),
					     _key_map(
					   {{sf::Keyboard::Unknown,	IWindow::NONE},
					    {sf::Keyboard::Space,	IWindow::SPACE},
					    {sf::Keyboard::Right,	IWindow::RIGHT},
					    {sf::Keyboard::Left,	IWindow::LEFT},
					    {sf::Keyboard::Up,		IWindow::UP},
					    {sf::Keyboard::Down,	IWindow::DOWN},
					    {sf::Keyboard::Num0,	IWindow::K_0},
					    {sf::Keyboard::Num1,	IWindow::K_1},
					    {sf::Keyboard::Num2,	IWindow::K_2},
					    {sf::Keyboard::Num3,	IWindow::K_3},
					    {sf::Keyboard::Num4,	IWindow::K_4},
					    {sf::Keyboard::Num5,	IWindow::K_5},
					    {sf::Keyboard::Num6,	IWindow::K_6},
					    {sf::Keyboard::Num7,	IWindow::K_7},
					    {sf::Keyboard::Num8,	IWindow::K_8},
					    {sf::Keyboard::Num9,	IWindow::K_9}})

{
  sf::VideoMode		size(winX, winY);

  std::cout << "[mSFML_Window::mSFML_Window] "
	    << windowName << " "
	    << winX << "x"
	    << winY
	    << std::endl;
  _window.create(size, windowName);
}

mSFML_Window::~mSFML_Window() {}

void			mSFML_Window::update(void) {}

bool			mSFML_Window::isAlive(void)
{
  return (_window.isOpen());
}

void			mSFML_Window::display(void)
{
  this->_window.draw(this->_string);
  _window.display();
}

void			mSFML_Window::clear(void)
{
  _window.clear(sf::Color::Black);
}

// Event
void			mSFML_Window::handleEvents(void)
{
  sf::Event		event;

  while (this->_window.pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::Closed:
	  if (DEBUG)
	    std::cout << "[Window::handleEvents] Closed window event" << std::endl;
	  this->_window.close();
	  break;
	case sf::Event::KeyPressed:
	  if (!this->_keyPressed(event))
	    this->_window.close();
	  break;
	case sf::Event::KeyReleased:
	  this->_keyReleased(event);
	  break;
	default:
	  break;
	}
    }
}

bool		        mSFML_Window::_keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
    {
      if (DEBUG)
  	std::cout << "[Window::handlemSFML_Keyboards] Closed window event" << std::endl;
      return (false);
    }
  else if (event.key.code)
    {
      auto search = this->_key_map.find(event.key.code);
      if (search != this->_key_map.end())
  	this->_current_key = search->second;
      else
  	std::cout << "[key pressed] => code : [" << event.key.code
  		  << "] /!\\ hasnt been found /!\\" << std::endl;
    }
  return (true);
}

void		        mSFML_Window::_keyReleased(sf::Event event)
{
  switch (event.key.code)
    {
    default:
      this->_current_key = NONE;
      break;
    }
}

IWindow::Key	        mSFML_Window::getKey(void) const
{
  return (this->_current_key);
}

/*
** Font mSFML
*/
void			mSFML_Window::loadFont(const std::string &path)
{
  this->_font.loadFromFile(path);
}

void			mSFML_Window::writeAt(const std::string &msg,
					      const float x, const float y,
					      const float size)
{
  this->_string.setFont(this->_font);
  this->_string.setString(msg);
  this->_string.setColor(sf::Color(255, 255, 255));
  this->_string.setScale(size, size);
  this->_string.setPosition(x, y);
}

/*
** Textures mSFML
*/
void			mSFML_Window::setTextureAt(const std::string &path,
						   const float x, const float y)
{
  sf::Sprite		sprite(*_manager.load(path));

  sprite.setPosition(x, y);
  // sprite.setScale(1., 1.);
  this->_window.draw(sprite);
}
