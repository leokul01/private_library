EXECUTABLE = private_library.out
CC = g++
FLAGS = -g -std=c++11 -I./include -Wall -Wextra -Werror
SOURCE_FILES = $(wildcard ./src/*.cpp)
OBJECT_FILES = $(patsubst %.cpp, %.o, $(SOURCE_FILES))

.PHONY: all clean fclean re

all: $(SOURCE_FILES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILES)
	$(CC) -o $@ $^ $(FLAGS)

.cpp.o:
	$(CC) -c -o $@ $< $(FLAGS)

lib:
	$(CC) -I./include/ -std=c++14 -shared -fPIC -Wl,-undefined,dynamic_lookup `python3 -m pybind11 --includes` example.cpp -o example`python3-config --extension-suffix`

clean:
	/bin/rm -f $(OBJECT_FILES)

fclean: clean
	/bin/rm -f $(EXECUTABLE)

re: fclean all
