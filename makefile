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
	g++ ./src/release/*.cpp ./build/*.o -I./include -o ./bin/midevil
	./bin/midevil -Wall

run:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -v ./bin/midevil -Wall

test:
	g++ ./src/test/*.cpp -I./include -L./build -o ./bin/test
	./bin/test -Wall

clean:
	find . -name '*.o' -delete
	find . -name '*~' -delete
