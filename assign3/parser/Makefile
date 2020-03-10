CFLAGS = -Wall -g -std=c11
BIN = 
INC = 
SRC = 
XML_PATH = /usr/include/libxml2


#executable for test (REMEMBER TO DELETE LATER)
# test: $(SRC)test.c $(BIN)libsvgparse.so
	# gcc $(CFLAGS) -L./bin $(SRC)test.c -I$(XML_PATH) -I$(INC) -o $(BIN)test -lsvgparse -lxml2


libsvgparse.so: LinkedListAPI.o SVGParser.o
	gcc -shared -o libsvgparse.so SVGParser.o LinkedListAPI.o -lxml2 -lm

SVGParser.o: SVGParser.c LinkedListAPI.h SVGParser.h
	gcc -c -fpic $(CFLAGS) -I$(XML_PATH) $(SRC)SVGParser.c -o $(BIN)SVGParser.o

LinkedListAPI.o: LinkedListAPI.c LinkedListAPI.h
	gcc -c -fpic $(CFLAGS) LinkedListAPI.c -o LinkedListAPI.o

clean:
	rm *.o *.so
