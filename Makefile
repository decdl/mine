
CC = g++
CXX_FLAGS = --std=c++17 `wx-config --cxxflags` $F
LD_FLAGS = `wx-config --libs` $F

all: mine

mine: Mine.o MineFrame.o MineUnit.o
	$(CC) $(LD_FLAGS) Mine.o MineFrame.o MineUnit.o -o mine

Mine.o: Mine.cpp prec.h.gch
	$(CC) $(CXX_FLAGS) -c Mine.cpp -o Mine.o

MineFrame.o: MineFrame.cpp prec.h.gch
	$(CC) $(CXX_FLAGS) -c MineFrame.cpp -o MineFrame.o

MineUnit.o: MineUnit.cpp prec.h.gch
	$(CC) $(CXX_FLAGS) -c MineUnit.cpp -o MineUnit.o

prec.h.gch: prec.h Mine.h MineFrame.h MineUnit.h
	$(CC) $(CXX_FLAGS) -c prec.h -o prec.h.gch

clean:
	rm -f *.gch *.o mine
