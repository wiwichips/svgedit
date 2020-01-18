#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"

int
main(int argc, char **argv)
{
	puts("hello1");
	SVGimage img;

	img.paths = NULL;

	getPaths(&img);
	
	free(createSVGimage("rect.svg"));
	
    return 0;
}
