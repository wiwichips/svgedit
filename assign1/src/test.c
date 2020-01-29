#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

int main(int argc, char **argv) {
	puts("hello1");

	SVGimage* gork = createSVGimage("testFiles/quad01.svg");
	
	puts("\n\n\ntesting stuff");
	printf("\tnum attri = {%d}\n", numAttr(gork));

/*
	puts("\n\nreturn num att");
	returnNumAttributes(gork, 0);
*/
	
	
	
/*	
	puts("\ntesting groyp 2 string");
	toString(gork->groups);
*/	
	puts("\n\ntesting delete");
	deleteSVGimage(gork);
	
    return 0;
}
