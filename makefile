CPP  = g++
OBJ = main.o \
	  quadrilatero.o \
	  solido.o \
	  degrade.o \
	  mascara.o \
	  vazado.o \
	  classes/display.o \
	  classes/glwindow.o
LIBS=-lSDLmain -lSDL -lGL -lGLU
FLAGS=

all: preenchimento

clean:
	rm -rf $(OBJ) preenchimento

preenchimento: $(OBJ)
	$(CPP) -o preenchimento $(OBJ) $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(FLAGS)

quadrilatero.o: quadrilatero.cpp
	$(CPP) -c quadrilatero.cpp -o quadrilatero.o $(FLAGS)

solido.o: solido.cpp
	$(CPP) -c solido.cpp -o solido.o $(FLAGS)
    
degrade.o: degrade.cpp
	$(CPP) -c degrade.cpp -o degrade.o $(FLAGS)
    
mascara.o: mascara.cpp
	$(CPP) -c mascara.cpp -o mascara.o $(FLAGS)
    
vazado.o: vazado.cpp
	$(CPP) -c vazado.cpp -o vazado.o $(FLAGS)
    
classes/glwindow.o: classes/glwindow.cpp
	$(CPP) -c classes/glwindow.cpp -o classes/glwindow.o $(FLAGS)

classes/display.o: classes/display.cpp
	$(CPP) -c classes/display.cpp -o classes/display.o $(FLAGS)

