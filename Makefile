SOURCES = $(wildcard sources/*.cpp)
OBJECTS = $(patsubst sources/%.cpp,sources/%.o,$(SOURCES))
NLOHMANN_INCLUDE = ./dependencies

CC = g++
CFLAGS = -Wall -Wextra -I$(NLOHMANN_INCLUDE) -std=c++17
LDFLAGS = -lm

all: battleship

battleship: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o battleship

sources/%.o : sources/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf sources/*.o battleship
