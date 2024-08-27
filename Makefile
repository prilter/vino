debug:
	clang++ -O3 src/main.cpp -o build/vild -lncurses
release:
	clang++ src/main.cpp -O3 -Oz -funroll-loops -fomit-frame-pointer -mtune=native -mno-omit-leaf-frame-pointer -fvectorize -flto -o build/vild -lncurses -std=c++20 -g0
