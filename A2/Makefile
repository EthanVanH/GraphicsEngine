FLAGS = -std=c++14 -Wall -Wextra -pedantic
LIBS = -lglut -lGLEW -lGLU -lGL -lglfw
SOURCEFILES = AssignmentTwo.cpp Cube.cpp Primatives.cpp Matrix.cpp Scene.cpp

all: Graphics

Graphics: Shapes
	g++ $(FLAGS) $(SOURCEFILES) -o Graphics $(LIBS)

Shapes:

clean: 
	rm -rf Graphics a.out shape.ppm output.ppm
