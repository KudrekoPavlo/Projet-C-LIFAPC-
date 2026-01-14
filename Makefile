all: bin/test

bin:
	mkdir -p bin

obj:
	mkdir -p obj

bin/test: obj/test.o obj/pixel.o obj/graphe.o obj/lodepng.o
		g++ -Wall -g obj/test.o obj/pixel.o obj/graphe.o  obj/lodepng.o -o bin/test.exe

obj/test.o: src/test.cpp src/pixel.h
		g++ -Wall -g -c src/test.cpp -o obj/test.o

obj/pixel.o:  src/pixel.cpp src/pixel.h
		g++  -Wall -g -c src/pixel.cpp -o obj/pixel.o

obj/graphe.o: src/graphe.cpp src/graphe.h src/lodepng.h
		g++ -Wall -g -c src/graphe.cpp -o obj/graphe.o 

obj/lodepng.o: src/lodepng.cpp src/lodepng.h
		g++ -Wall -g -c src/lodepng.cpp -o obj/lodepng.o

clean: 
		rm obj/*.o