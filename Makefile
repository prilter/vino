debug:
	clang++ src/main.cpp -c
	clang++ src/fileworking.cpp -c
	clang++ src/vild.cpp -c
	clang++ *.o -o bin/vild -std=c++17 -lncurses
	rm *.o
	./bin/vild t.t
