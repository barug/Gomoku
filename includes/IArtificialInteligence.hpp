#ifndef IARTIFICIAL_INTELIGENCE_HPP
# define IARTIFICIAL_INTELIGENCE_HPP

# include "Map.hpp"

class				IArtificialInteligence
{

public:
  virtual Map::Coordinates	computeNextAction(const Map &map) = 0;
};

#endif /* IARTIFICIAL_INTELIGENCE_HPP */
