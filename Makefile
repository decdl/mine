
CC = g++
CXX_FLAGS = --std=c++17 `wx-config --cxxflags` $F
LD_FLAGS = `wx-config --libs` $F

all: mine

mine: Mine.o MineFrame.o MineUnit.o
	$(CC) $(LD_FLAGS) Mine.o MineFrame.o MineUnit.o -o mine

Mine.o: Mine.cpp precompile.h.gch
	$(CC) $(CXX_FLAGS) -c Mine.cpp -o Mine.o

MineFrame.o: MineFrame.cpp precompile.h.gch
	$(CC) $(CXX_FLAGS) -c MineFrame.cpp -o MineFrame.o

MineUnit.o: MineUnit.cpp precompile.h.gch
	$(CC) $(CXX_FLAGS) -c MineUnit.cpp -o MineUnit.o

precompile.h.gch: precompile.h Mine.h MineFrame.h MineUnit.h
	$(CC) $(CXX_FLAGS) -c precompile.h -o precompile.h.gch

clean:
	rm -f *.gch *.o mine
