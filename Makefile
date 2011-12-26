CC = g++

CXXFLAGS = -Wall
LDFLAGS = 

BINS = Connect4

all: ${BINS}

Board.o: Board.cc Board.hh
GameHandler.o: GameHandler.hh GameHandler.cc
Connect4: Board.o GameHandler.o main.cc 
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -rf ${BINS} *.o
