a.out: save.h board.h entity.h print.h colors.h globals.h  main.cc
	g++ -std=c++11 -g main.cc -lncurses
#	g++ -std=c++11 -O3 main.cc -lncurses
format:	
	reformat ./*.h ./*.cc
	g++ -std=c++11 -g main.cc -lncurses

