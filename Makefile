OBJ=solution.o walk.o main.o saw.o gvcsolution.o solver.o sawj.o graph.o
DOBJ= $(OBJ:.o=.do)

DATE=$(shell date +%Y%m%d)

CXXFLAGS=-std=c++0x -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG -DVERSION=$(DATE)
DCXXFLAGS=-std=c++0x -O0 -W -Wall -g3 -DVERSION=$(DATE)

BIN=B.solv

all: release

release: $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o $(BIN)
	strip $(BIN)

debug: $(DOBJ)
	g++ $(DCXXFLAGS) $(DOBJ) -o $(BIN)

%.o : %.cpp *.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

%.do : %.cpp *.h
	$(CXX) -c $(DCXXFLAGS) $< -o $@

archive:
	tar -cjvf $(BIN)_$(DATE).tar.bz *.cpp *.h README.txt Makefile

clean:
	rm -f *.o *.do $(BIN)
