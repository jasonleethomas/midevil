FLG=-Wall
INC=./include
LNK=./libs
DEP=
SRC=./src
BIN=./bin
LOG=./log.txt

all: 
	g++ ./src/debug/*.cpp -c -I$(INC)

debug: SRC:=./src/debug
debug: 
	g++ $(SRC)/*.cpp -c -I$(INC); \
	mv *.o $(LNK)

release: SRC:=./src/release
release: 
	g++ $(SRC)/*.cpp -c -$(INC); \
	mv *.o $(LNK)

clean:
	rm *.o	
