FLG=-Wall
INC=./include
LIB=./libs
BLD=./build
BIN=./bin/midevil
LOG=./log.txt
DBG=./src/debug
RLS=./src/release

all:
	g++ ./src/debug/*.cpp -I./include -c ./build
	mv ./*.o ./build

debug:
	g++ ./src/debug/*.cpp -I./include -c ./build
	mv ./*.o ./build
	
release: 
	g++ ./src/debug/*.cpp ./src/release/*.cpp -I./include -L./libs -o ./bin/midevil
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -v ./bin/midevil -Wall

test:
	g++ ./src/debug/*.cpp ./src/test/*.cpp -I./include  -L./libs -o ./bin/test
	./bin/test -Wall

clean:
	find . -name '*.o' -delete
	find . -name '*~' -delete	
