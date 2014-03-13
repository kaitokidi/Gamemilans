# Makefile super op

all: main.o board.o logica.o ia.o presentacio.o everything 

exe: main.o board.o logica.o ia.o presentacio.o everything executethegaem

murs: main.o board.o logica.o ia.o presentacio.o everything murs

onlines: main.o board.o logica.o ia.o presentacio.o everything onlinese

onlinec: main.o board.o logica.o ia.o presentacio.o everything onlinecl

ia: main.o board.o logica.o ia.o presentacio.o everything usingia
	
ia.o: ia.*
	g++ -c ia.cpp

presentacio.o: presentacio.*
	g++ -c presentacio.cpp

main.o: main.cpp
	g++ -c main.cpp
	
board.o: board.*
	g++ -c board.cpp 

logica.o: logica.*
	g++ -c logica.cpp
	
everything:
	g++ -o gamemilans main.o board.o logica.o ia.o presentacio.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
		
executethegaem:
	./gamemilans
	
murs:
	./gamemilans 22
	
onlinese: 
	./gamemilans 0 S
	
onlinecl: 
	./gamemilans 0 c

usingia:
	./gamemilans 0 I
	
clear:
	rm *.o