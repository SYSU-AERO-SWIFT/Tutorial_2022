vpath %.cpp src
vpath %.hpp include
TAR = main
OBJ = main.o Recovery.o

$(TAR):$(OBJ)
	g++ $@ -o $^
main.o: src/main.cpp include/Recovery.hpp
	g++ -c src/main.cpp -o main.o
Recovery.o: src/Recovery.cpp include/Recovery.hpp
	g++ -c src/Recovery.cpp -o include/Recovery.hpp
.PHONY: clearall clear
clearall: 
	rm -rf $(OBJ) $(TAR)
clear:
	rm -rf $(OBJ)

