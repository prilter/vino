debug:
	clang++ src/*.cpp -o bin/vild -std=c++17 -lncurses
	./bin/vild t.t
