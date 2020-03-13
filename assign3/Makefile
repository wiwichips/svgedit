CFLAGS = -Wall -g -std=c11
BIN =parser/
INC =parser/
SRC =parser/
XML_PATH = /usr/include/libxml2


#executable for test (REMEMBER TO DELETE LATER)
# test: $(SRC)test.c $(BIN)libsvgparse.so
	# gcc $(CFLAGS) -L./bin $(SRC)test.c -I$(XML_PATH) -I$(INC) -o $(BIN)test -lsvgparse -lxml2


libsvgparse.so: $(BIN)LinkedListAPI.o $(BIN)SVGParser.o
	gcc -shared -o libsvgparse.so $(BIN)SVGParser.o $(BIN)LinkedListAPI.o -lxml2 -lm

$(BIN)SVGParser.o: $(SRC)SVGParser.c $(INC)LinkedListAPI.h $(INC)SVGParser.h
	gcc -c -fpic $(CFLAGS) -I$(XML_PATH) $(SRC)SVGParser.c -o $(BIN)SVGParser.o

$(BIN)LinkedListAPI.o: $(SRC)LinkedListAPI.c $(INC)LinkedListAPI.h
	gcc -c -fpic $(CFLAGS) $(SRC)LinkedListAPI.c -o $(BIN)LinkedListAPI.o

clean:
	cd parser
	rm -f *.o *.so
	cd ..
	rm -f *.o *.so
