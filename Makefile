EXEC=cube

CXX=g++

BUILDDIR=build

SRC=main.cpp disp.cpp prog.cpp util.cpp

HDR=math.h

OBJ=$(SRC:%.cpp=$(BUILDDIR)/%.o)

LDFLAGS=-lSDL2 -lGLEW -lGL

.PHONY: all
all: mk_build $(EXEC)

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@

$(EXEC): $(OBJ) $(HDR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o $(EXEC)
