EXECUTABLE = books_library.out
CC = g++
FLAGS = -g -Wall -Wextra -Werror -std=c++11 -I./include 
SRC	= src
OBJ = obj
SOURCE_FILES = $(wildcard ./$(SRC)/*.cpp)
OBJECT_FILES = $(patsubst %.cpp, %.o, $(SOURCE_FILES))

.PHONY: all clean fclean re

all: $(SOURCE_FILES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILES)
	$(CC) -o $@ $^ $(FLAGS)

.cpp.o:
	$(CC) -c -o $@ $< $(FLAGS)

clean:
	/bin/rm -f $(OBJECT_FILES)

fclean: clean
	/bin/rm -f $(EXECUTABLE)

re: fclean all
