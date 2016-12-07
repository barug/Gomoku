//
// mSFML_Window.cpp for mSFML in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/mSFML
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Wed Nov 16 17:14:22 2016 Thomas Billot
// Last update Tue Dec  6 12:10:06 2016 Thomas Billot
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
					   {{sf::Keyboard::Unknown,	IGui::NONE},
					    {sf::Keyboard::Space,	IGui::SPACE},
					    {sf::Keyboard::Right,	IGui::RIGHT},
					    {sf::Keyboard::Left,	IGui::LEFT},
					    {sf::Keyboard::Up,		IGui::UP},
					    {sf::Keyboard::Down,	IGui::DOWN},
					    {sf::Keyboard::Num0,	IGui::K_0},
					    {sf::Keyboard::Num1,	IGui::K_1},
					    {sf::Keyboard::Num2,	IGui::K_2},
					    {sf::Keyboard::Num3,	IGui::K_3},
					    {sf::Keyboard::Num4,	IGui::K_4},
					    {sf::Keyboard::Num5,	IGui::K_5},
					    {sf::Keyboard::Num6,	IGui::K_6},
					    {sf::Keyboard::Num7,	IGui::K_7},
					    {sf::Keyboard::Num8,	IGui::K_8},
					    {sf::Keyboard::Num9,	IGui::K_9}})

{
  sf::VideoMode		size(winX, winY);

  std::cout << "[mSFML_Window::mSFML_Window] "
	    << windowName << " "
	    << winX << "x"
	    << winY
	    << std::endl;
  _window.create(size, windowName);
}

mSFML_Window::mSFML_Window(const std::string &fontPath,
			   const std::string &windowName,
			   const int winX,
			   const int winY) : _window(),
					     _winX(winX),
					     _winY(winY),
					     _current_key(NONE),
					     _key_map(
					   {{sf::Keyboard::Unknown,	IGui::NONE},
					    {sf::Keyboard::Space,	IGui::SPACE},
					    {sf::Keyboard::Right,	IGui::RIGHT},
					    {sf::Keyboard::Left,	IGui::LEFT},
					    {sf::Keyboard::Up,		IGui::UP},
					    {sf::Keyboard::Down,	IGui::DOWN},
					    {sf::Keyboard::Num0,	IGui::K_0},
					    {sf::Keyboard::Num1,	IGui::K_1},
					    {sf::Keyboard::Num2,	IGui::K_2},
					    {sf::Keyboard::Num3,	IGui::K_3},
					    {sf::Keyboard::Num4,	IGui::K_4},
					    {sf::Keyboard::Num5,	IGui::K_5},
					    {sf::Keyboard::Num6,	IGui::K_6},
					    {sf::Keyboard::Num7,	IGui::K_7},
					    {sf::Keyboard::Num8,	IGui::K_8},
					    {sf::Keyboard::Num9,	IGui::K_9}})

{
  sf::VideoMode		size(winX, winY);
  this->loadFont(fontPath);
  std::cout << "[mSFML_Window::mSFML_Window] "
	    << windowName << " "
	    << winX << "x"
	    << winY
	    << std::endl;
  _window.create(size, windowName);
}

mSFML_Window::~mSFML_Window() {}

/*
** Window
*/
void			mSFML_Window::update(void) {}

bool			mSFML_Window::isAlive(void)
{
  return (_window.isOpen());
}

void			mSFML_Window::display(void)
{
  _window.display();
}

void			mSFML_Window::clear(void)
{
  _window.clear(sf::Color::Black);
}

/*
** Keyboard Event
*/
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
	  if (event.key.code == sf::Keyboard::Escape)
	    {
	      if (DEBUG)
		std::cout << "[Window::handleEvents] Closed window event" << std::endl;
	      this->_window.close();
	    }
	  else if (event.key.code)
	    {
	      if ((this->_current_key = this->_key_map[event.key.code]) == NONE)
		std::cout << "[key pressed] => code : [" << event.key.code
			  << "] /!\\ hasnt been found /!\\" << std::endl;
	    }
	  break;
	case sf::Event::KeyReleased:
	  switch (event.key.code)
	    {
	    default:
	      this->_current_key = NONE;
	      break;
	    }
	  break;
	default:
	  break;
	}
    }
}

IGui::Key	        mSFML_Window::getKey(void) const
{
  return (this->_current_key);
}

/*
** Mouse Events
*/
unsigned int		mSFML_Window::getMouseX(void) const
{
  return (this->_mouse.getPosition(this->_window).x);
}

unsigned int		mSFML_Window::getMouseY(void) const
{
  return (this->_mouse.getPosition(this->_window).y);
}

bool			mSFML_Window::buttonLeftIsClicked(void) const
{
  return (this->_mouse.isButtonPressed(sf::Mouse::Button::Left));
}

bool			mSFML_Window::buttonRightIsClicked(void) const
{
  return (this->_mouse.isButtonPressed(sf::Mouse::Button::Right));
}

/*
** Font
*/
void			mSFML_Window::loadFont(const std::string &path)
{
  this->_font.loadFromFile(path);
}

void			mSFML_Window::writeAt(const std::string &msg,
					      const float x, const float y,
					      const unsigned int hexaColorCode,
					      const float scale)
{
  std::vector<unsigned int> rgb = hexaToRgb(hexaColorCode);
  sf::Text text;

  text.setFont(this->_font);
  text.setString(msg);
  text.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2]));
  text.setScale(scale, scale);
  text.setPosition(x, y);
  this->_window.draw(text);
}

/*
** Textures
*/
void			mSFML_Window::setTextureAt(const std::string &path,
						   const float x, const float y,
						   const float scale)
{
  sf::Sprite		sprite;
  const sf::Texture	*texture;

  if ((texture = _manager.load(path)) == NULL)
    throw std::out_of_range("Failed to load texture " + path);
  sprite.setTexture(*texture);
  sprite.setPosition(x, y);
  sprite.setScale(scale, scale);
  this->_window.draw(sprite);
}

/*
** Fill Rectangle
*/
void			mSFML_Window::fillRec(const unsigned int x,
					      const unsigned int y,
					      const unsigned int i,
					      const unsigned int j,
					      const unsigned int hexaColorCode,
					      const unsigned int alpha)
{
  std::vector<unsigned int> rgb = hexaToRgb(hexaColorCode);
  sf::RectangleShape rectangle;

  rectangle.setPosition(sf::Vector2f(x, y));
  rectangle.setSize(sf::Vector2f(i, j));
  rectangle.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2], alpha));
  this->_window.draw(rectangle);
}

void			mSFML_Window::fillCircle(const unsigned int x,
						 const unsigned int y,
						 const unsigned int i,
						 const unsigned int j,
						 const unsigned int hexaColorCode)
{
  std::vector<unsigned int> rgb = hexaToRgb(hexaColorCode);
  sf::CircleShape circle;

  circle.setPosition(x, y);
  circle.setScale(sf::Vector2f(i, j));
  circle.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2], 255));
  this->_window.draw(circle);
}


bool		        mSFML_Window::magnetTile(const unsigned int mouseX,
						 const unsigned int mouseY,
						 const unsigned int x,
						 const unsigned int y,
						 const unsigned int intensityX,
						 const unsigned int intensityY) const
{
  for (unsigned int i = 0; i < intensityX; i++)
    for (unsigned int j = 0; j < intensityY; j++)
      if ((mouseX + i == x and mouseY + i == y) ||
	  (mouseX + i == x and mouseY + j == y) ||
	  (mouseX + j == x and mouseY + j == y) ||
	  (mouseX + j == x and mouseY + i == y) ||

	  (mouseX + i == x and mouseY - i == y) ||
	  (mouseX + i == x and mouseY - j == y) ||
	  (mouseX + j == x and mouseY - j == y) ||
	  (mouseX + j == x and mouseY - i == y) ||

	  (mouseX - i == x and mouseY + i == y) ||
	  (mouseX - i == x and mouseY + j == y) ||
	  (mouseX - j == x and mouseY + j == y) ||
	  (mouseX - j == x and mouseY + i == y) ||

	  (mouseX - i == x and mouseY - i == y) ||
	  (mouseX - i == x and mouseY - j == y) ||
	  (mouseX - j == x and mouseY - j == y) ||
	  (mouseX - j == x and mouseY - i == y))
	return (true);
  return (false);
}
