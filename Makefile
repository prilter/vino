debug:
	g++ src/main.cpp -c
	g++ src/fileworking.cpp -c
	g++ src/vild.cpp -c
	g++ *.o -o bin/vild -std=c++17 -lncurses
	rm *.o
	./bin/vild t.t
