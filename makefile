CC := g++
CXXFLAGS := -Wall -Wextra -g -O3 -std=c++17

SAMEGAME_DEP_OBJ := samegame.o BoardState.o SearchUtils.o
Header := BoardState.h SearchUtils.h

all: samegame

%.o: %.C DEPS Header
	$(CC) $(CXXFLAGS) -c -o $@ $<

samegame: $(SAMEGAME_DEP_OBJ)
	${CC} ${CXXFLAGS} -o samegame $^

clean:
	rm -f samegame *.o
