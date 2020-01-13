UNAME := $(shell uname)
CC = gcc
CFLAGS = -Wall -std=c11 -g -Iinclude
SRC = src/
BIN = bin/
INC = include

#change the inlcude path depending on operating system
ifeq ($(UNAME), Linux)
	INC_PATH = /usr/include/libxml2
endif
ifeq ($(UNAME), Darwin)
	INC_PATH = /System/Volumes/Data/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/libxml2
endif

#executable for test (REMEMBER TO DELETE LATER)
l: $(SRC)test.c SVGParser.so liblist.so
	$(CC) $(CFLAGS) $(SRC)test.c -lxml2 -I$(INC_PATH) -o bin/l

#shared library for svg parser
SVGParser.so: $(SRC)SVGParser.c
	$(CC) -I$(INC_PATH) $(SRC)SVGParser.c  $(CFLAGS) -lxml2 -shared -o bin/SVGParser.so

#shared library for linked list api
liblist.so: $(SRC)LinkedListAPI.c
	$(CC) $(SRC)LinkedListAPI.c $(CFLAGS) -shared -o bin/liblist.so
