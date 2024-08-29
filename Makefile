debug:
	clang++ src/fileworking.cpp -c
	clang++ src/vild.cpp -c
	clang++ src/main.cpp -c
	clang++ *o -o bin/vild -std=c++17 -lncurses
	rm *.o
go:
	./bin/vild t.t
