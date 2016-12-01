##
## Makefile for Gomoku in /home/mikaz3/Tek3/B5/AI
## 
## Made by Thomas Billot
## Login   <mikaz3@epitech.net>
## 
## Started on  Wed Oct 12 12:28:14 2016 Thomas Billot
## Last update Wed Nov 30 15:17:09 2016 Thomas Billot
##

CXX 	= g++

RM	= rm -f

SRCS	= srcs/Main.cpp 		\
	  srcs/Gomoku.cpp		\
	  srcs/mSFML_Window.cpp		\
	  srcs/mSFML_Audio.cpp		\
	  srcs/Case.cpp			\
	  srcs/TextureManager.cpp	\
	  srcs/Map.cpp			\

OBJS	= $(SRCS:.cpp=.o)

BIN	= Gomoku

SFMLFLAGS += -lsfml-graphics
SFMLFLAGS += -lsfml-system
SFMLFLAGS += -lsfml-window
SFMLFLAGS += -lsfml-audio

CXXFLAGS += -W -Wall -Wextra -Werror
CXXFLAGS += $(SFMLFLAGS)
CXXFLAGS += -Iincludes/
CXXFLAGS += -std=c++11

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(CXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(BIN)

re: fclean all

.PHONY: all clean fclean re
