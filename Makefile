debug:
	g++ src/main.cpp -c
	g++ src/fileworking.cpp -c
	g++ src/vino.cpp -c
	g++ *.o -o bin/vino -std=c++17 -lncurses
	rm *.o
