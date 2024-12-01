SOURCES = $(wildcard sources/*.cpp)
OBJECTS = $(patsubst sources/%.cpp,sources/%.o,$(SOURCES))

CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -I/opt/homebrew/include
LDFLAGS = -lm

all: battleship

battleship: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o battleship

sources/%.o : sources/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf sources/*.o battleship
