debug:
	g++ src/main.cpp -c
	g++ src/fileworking.cpp -c
	g++ src/terminal_mode/f_term.cpp -c
	g++ src/vino.cpp -c
	g++ *.o -o bin/vino -std=c++17 -lncurses
	rm *.o

release:
	clang++ -fno-rtti -mtune=native -march=native -msse3 -mavx2 -ffast-math -funroll-loops -O3 src/main.cpp -c
	clang++ -fno-rtti -mtune=native -march=native -msse3 -mavx2 -ffast-math -funroll-loops -O3 src/fileworking.cpp -c
	clang++ -fno-rtti -mtune=native -march=native -msse3 -mavx2 -ffast-math -funroll-loops -O3 src/terminal_mode/f_term.cpp -c
	clang++ -fno-rtti -mtune=native -march=native -msse3 -mavx2 -ffast-math -funroll-loops -O3 src/vino.cpp -c
	clang++ -fno-rtti -mtune=native -fno-exceptions -flto -march=native -msse3 -mavx2 -ffast-math -funroll-loops -O3 *.o -o bin/vino -lncurses
	rm *.o
