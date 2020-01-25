#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"

int main(int argc, char **argv) {
	puts("hello1");
	SVGimage img;

	img.paths = NULL;

	getPaths(&img);
	SVGimage* gork = createSVGimage("Emoji_poo.svg");
	
	puts("\n\n\ntesting stuff");
	printf("\tnum attri = {%d}\n", numAttr(gork));
	
	puts("testing delete");
	deleteSVGimage(gork);
	
    return 0;
}
