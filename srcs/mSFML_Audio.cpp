# include <iostream>
# include "mSFML_Audio.hpp"

mSFML_Audio::mSFML_Audio()
{}

mSFML_Audio::~mSFML_Audio()
{}

void		mSFML_Audio::loadSound(const std::string &path)
{
  if (this->_sound.getBuffer())
    this->_sound.resetBuffer();
  try
    {
      if (!this->_buffer.loadFromFile(path))
	throw ("[SFML::AUDIO::loadSound] Impossible to load" + path);
    }
  catch (const std::string & error)
    {
      std::cerr << error << std::endl;
    }
  this->_sound.setBuffer(this->_buffer);
}

void	        mSFML_Audio::loadMusic(const std::string &path)
{
  try
    {
      if (!this->_music.openFromFile(path))
	throw ("[SFML::AUDIO::loadMusic] Impossible to load" + path);
    }
  catch (const std::string & error)
    {
      std::cerr << error << std::endl;
    }
}

void		mSFML_Audio::musicPlay()
{
  this->_music.play();
}

void	        mSFML_Audio::musicPause()
{
  this->_music.pause();
}

void		mSFML_Audio::musicStop()
{
  this->_music.stop();
}

void		mSFML_Audio::musicSetVolume(const unsigned int volume)
{
  this->_music.setVolume(volume);
}

void		mSFML_Audio::musicSetLoop(const bool isloop)
{
  this->_music.setLoop(isloop);
}

void		mSFML_Audio::soundPlay()
{
  this->_sound.play();
}

void		mSFML_Audio::soundSetVolume(const unsigned int volume)
{
  this->_sound.setVolume(volume);
}

void		mSFML_Audio::soundSetLoop(const bool isloop)
{
  this->_sound.setLoop(isloop);
}
