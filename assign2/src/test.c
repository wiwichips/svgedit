#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

int main(int argc, char **argv) {
	
	puts("\n\ncreate svgimage");
	SVGimage* gork = createSVGimage("testFilesA2/rects.svg");
	
	freeListDataStructure(getRects(gork));
	freeListDataStructure(getCircles(gork));
//	freeListDataStructure(getGroups(gork));
	freeListDataStructure(getPaths(gork));
	
	printf("numRectsWithArea = %d\n", numRectsWithArea(gork, 1));
	printf("numCirclesWithArea = %d\n", numCirclesWithArea(gork, 1));
	printf("numPathsWithdata = %d\n", numPathsWithdata(gork, "test"));
//	printf("numGroupsWithLen = %d\n", numGroupsWithLen(gork, 1));
	
	printf("numAttr = %d\n", numAttr(gork));
	
	free(SVGimageToString(gork));
	
	puts("\n\ntesting delete");
	deleteSVGimage(gork);
	
    return 0;
}

