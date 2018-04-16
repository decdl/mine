CXXFLAGS += --std=c++17 `wx-config --cxxflags`
LDFLAGS += `wx-config --libs`

all: mine

mine: Mine.o MineFrame.o MineUnit.o
	$(CXX) $(LDFLAGS) Mine.o MineFrame.o MineUnit.o -o mine

Mine.o: Mine.cpp prec.h.gch
	$(CXX) $(CXXFLAGS) -c Mine.cpp -o Mine.o

MineFrame.o: MineFrame.cpp prec.h.gch
	$(CXX) $(CXXFLAGS) -c MineFrame.cpp -o MineFrame.o

MineUnit.o: MineUnit.cpp prec.h.gch
	$(CXX) $(CXXFLAGS) -c MineUnit.cpp -o MineUnit.o

prec.h.gch: prec.h Mine.h MineFrame.h MineUnit.h
	$(CXX) $(CXXFLAGS) -c prec.h -o prec.h.gch

clean:
	rm -f *.gch *.o mine
