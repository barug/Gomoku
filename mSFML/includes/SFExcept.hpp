//
// SFExcept.hpp for mSFML
//
// Made by Thomas Bogard
// Login   <bogard_t@epitech.net>
//
// Started on  Wed Oct 16 09:51:10 2016 Thomas Bogard
// Last update Tue Oct 18 01:08:49 2016 Bogard
//

#ifndef		_EXCEPT_HPP_
# define	_EXCEPT_HPP_

# include	<exception>

namespace sf
{
  class		Except : public std::exception
  {
  public:
    SFExcept(std::string error = "") throw()
      : _error(error)
    {
    }

    virtual ~SFExcept() throw()
    {
    }

    virtual const char *what() const throw()
    {
      return (this->_error.c_str());
    }

  private:
    std::string	_error;
  };
}

#endif		// !_EXCEPT_HPP_
