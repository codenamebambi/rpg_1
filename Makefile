a.out: save.h board.h entity.h print.h colors.h general.h  main.cc
	g++ -std=c++11 -g main.cc -lncurses
optimize:	
	g++ -std=c++11 -O3 main.cc -lncurses
format:	
	reformat ./*.h ./*.cc
	g++ -std=c++11 -g main.cc -lncurses
clean:
	rm ./a.out ./*.gch
