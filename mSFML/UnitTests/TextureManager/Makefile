##
## Makefile for Gomoku in /home/mikaz3/Tek3/B5/AI
## 
## Made by Thomas Billot
## Login   <mikaz3@epitech.net>
## 
## Started on  Wed Oct 12 12:28:14 2016 Thomas Billot
## Last update Sat Nov 19 15:56:05 2016 Thomas Billot
##

CXX 	= g++

RM	= rm -f

SRCS	= main.cpp 		\
	  TextureManager.cpp	\
	  mSFML_Textures.cpp	\

OBJS	= $(SRCS:.cpp=.o)

BIN	= TextureManagerTest

SFMLFLAGS += -lsfml-graphics
SFMLFLAGS += -lsfml-audio
SFMLFLAGS += -lsfml-system
SFMLFLAGS += -lsfml-graphics

CXXFLAGS += -W -Wall -Wextra -Werror
CXXFLAGS += $(SFMLFLAGS)
CXXFLAGS += -I.
CXXFLAGS += -std=c++11
CXXFLAGS += -g -ggdb -g3

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(CXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(BIN)

re: fclean all

.PHONY: all clean fclean re
