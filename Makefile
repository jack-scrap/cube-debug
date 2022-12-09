CXX=g++

SRC=main.cpp disp.cpp prog.cpp util.cpp
OBJ=$(SRC:%.cpp=%.o)

LDFLAGS=-lSDL2 -lGLEW -lGL

.PHONY: all
all: a.out

%.o: %.cpp %.h
	$(CXX) -c $< -o $@

main.o: main.cpp
	$(CXX) -c $< -o $@

a.out: $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm *.o a.out
