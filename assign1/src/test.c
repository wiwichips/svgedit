#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

int main(int argc, char **argv) {
	
	puts("\n\ncreate svgimage");
	SVGimage* gork = createSVGimage("testFiles/Emoji_poo.svg");
	
	puts("\n\ntesting circles");
	getCircles(gork);
	
	puts("\n\ntesting delete");
	deleteSVGimage(gork);
	
    return 0;
}
