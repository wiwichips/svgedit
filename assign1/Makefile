UNAME := $(shell uname)
CC = gcc
CFLAGS = -Wall -std=c11 -g -Iinclude
SRC = src/
BIN = bin/
INC = include/
LDFLAGS = -L./bin

#change the inlcude path depending on operating system
ifeq ($(UNAME), Linux)
	INC_PATH = /usr/include/libxml2
endif
ifeq ($(UNAME), Darwin)
	INC_PATH = /System/Volumes/Data/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/libxml2
endif

#executable for test (REMEMBER TO DELETE LATER)
test: $(SRC)test.c libsvgparse.so liblist.so 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC)test.c -I$(INC_PATH) -o bin/test -llist -lsvgparse -lxml2

#test: $(SRC)test.c SVGParser.so liblist.so
#	$(CC) $(CFLAGS) -I$(INC_PATH) $(SRC)test.c -lxml2 -o test

#shared library for svg parser
libsvgparse.so: $(SRC)SVGParser.c $(INC)SVGParser.h
	$(CC) -I$(INC_PATH) $(SRC)SVGParser.c  $(CFLAGS) -lxml2 -shared -o bin/libsvgparse.so

#shared library for linked list api
liblist.so: $(SRC)LinkedListAPI.c $(INC)LinkedListAPI.h
	$(CC) $(SRC)LinkedListAPI.c $(CFLAGS) -shared -o bin/liblist.so

clean:
	rm -rfv bin/*.so bin/*.o