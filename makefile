FLG=-Wall
INC=./include
LIB=./libs
BLD=./build
SRC=./src
BIN=./bin
LOG=./log.txt

all:
	g++ ./src/debug/*.cpp -c -I$(INC)
	mv ./*.o $(BLD)

debug: SRC:=./src/debug
debug:
	g++ $(SRC)/*.cpp -c -I$(INC)
	mv ./*.o $(BLD)

release: SRC:=./src/release
release: 
	g++ $(SRC)/*.cpp -c -$(INC)
	mv ./*.o $(BLD)

clean:
	find . -name '*.o' -delete
	find . -name '*~' -delete	
