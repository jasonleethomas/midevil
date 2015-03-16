FLG=-Wall
INC=./include
LIB=./libs
BLD=./build
SRC=./src
BIN=./bin/midevil
LOG=./log.txt

all:
	g++ ./src/debug/*.cpp -c -I$(INC)
	mv ./*.o $(BLD)

debug: SRC:=./src/debug
debug:
	g++ $(SRC)/*.cpp -I$(INC) -o $(BIN)
	valgrind --tool=memcheck --leak-check=full -v $(BIN) -Wall

release: SRC:=./src/release/midevil.cpp
release: 
	g++ $(SRC)/*.cpp -c -$(INC)
	mv ./*.o $(BLD)

clean:
	find . -name '*.o' -delete
	find . -name '*~' -delete	
