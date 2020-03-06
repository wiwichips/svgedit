#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

#define SCH "testFilesA2/svg.xsd"

int testingNumber = 0;
int debug = 0;

int dain(int argc, char **argv);
void test1(SVGimage* gork);
void putsError(char* string);
int bain();
int gain();
int tesingGroups();
int oldmain(int argc, char **argv);
void hen_and_chicksToFile();
void david();
void chris();
void mainTestThing(char* fileName1, char* fileName2);
int minDriver();

int main() {
	
	SVGimage* img = createSVGimage("rect.svg");
	
	
	
	Rectangle* r = JSONtoRect("{\"x\":1,\"y\":2,\"w\":3,\"h\":4,\"units\":\"cm\"}\n");
	
	printf("x = %lf, y = %lf, w = %lf, h = %lf\n", r->x, r->y, r->width, r->height);
	printf("units = %s\n", r->units);
	
	
	
	deleteSVGimage(img);
	return 0;
}

