CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

clean: 
	/bin/rm main
main: 
	src/main.cpp ; g++  $(CXXFLAGS)  src/main.cpp   -o   main
run: 
	./main
all: main
	./main
valgrind: 
	valgrind ./main
valgrindplus:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes ./main
