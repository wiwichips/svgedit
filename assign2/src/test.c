#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

int main(int argc, char **argv) {
	
	puts("\n\ncreate svgimage");
	SVGimage* gork = createSVGimage("Wink_Brutal_Test_2.svg");
	
	puts("\n\ntesting circles");
	
	puts("\n\ntesting delete");
	deleteSVGimage(gork);
	
    return 0;
}
