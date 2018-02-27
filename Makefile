# define libraries
LIB = -lGL -lGLU -lglut
#LIB2 = libim/libim.a jpeg/libjpeg.a

# define makefile targets
CC = g++ -Wall
BIN = Circle Cylinder

#all: $(LIB2) $(BIN)
all: $(BIN)

clean:
	/bin/rm -f $(BIN)

#jpeg/libjpeg.a:
#	cd jpeg;make;cd ..
#libim/libim.a:
#	cd libim;make;cd ..

Circle: circle.cpp
	$(CC) -o circle circle.cpp $(LIB)

Cylinder: cylinder.cpp
	$(CC) -o cylinder cylinder.cpp $(LIB)
